/*================================================================================
*     Source: ../RCM/StrategyStudio/examples/strategies/CombinedStrategy/CombinedStrategy.cpp
*================================================================================*/

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "CombinedStrategy.h"
#include <Utilities/utils.h>
#include <iostream>

using namespace RCM::StrategyStudio;

CombinedStrategy::CombinedStrategy(StrategyID strategyID, const std::string& strategyName, const std::string& groupName)
    : Strategy(strategyID, strategyName, groupName), position_size_(100), aggressiveness_(0.01) {}

CombinedStrategy::~CombinedStrategy() {}

void CombinedStrategy::OnResetStrategyState() {
    vwap_bollinger_map_.clear();
}

void CombinedStrategy::DefineStrategyParams() {
    params().CreateParam(CreateStrategyParamArgs("position_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, position_size_));
    params().CreateParam(CreateStrategyParamArgs("aggressiveness", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, aggressiveness_));
}

void CombinedStrategy::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate) {
    for (SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 10);
    }
}

void CombinedStrategy::OnBar(const BarEventMsg& msg) {
    const Instrument* instrument = &msg.instrument();
    double price = msg.bar().close();
    double volume = msg.bar().volume();

    // Initialize VWAPBollinger if not already tracking
    if (vwap_bollinger_map_.find(instrument) == vwap_bollinger_map_.end()) {
        vwap_bollinger_map_[instrument] = VWAPBollinger(20, 2.0);
    }

    VWAPBollinger& vwap_bollinger = vwap_bollinger_map_[instrument];
    vwap_bollinger.Update(price, volume);

    // Check trading signal
    if (vwap_bollinger.FullyInitialized()) {
        double vwap = vwap_bollinger.VWAP();
        double upper_band = vwap_bollinger.UpperBand();
        double lower_band = vwap_bollinger.LowerBand();

        int desired_position = 0;
        if (price <= lower_band && price < vwap) {
            desired_position = position_size_;
        } else if (price >= upper_band && price > vwap) {
            desired_position = -position_size_;
        }

        AdjustPortfolio(instrument, desired_position);
    }
}

void CombinedStrategy::AdjustPortfolio(const Instrument* instrument, int desired_position) {
    int trade_size = desired_position - portfolio().position(instrument);
    if (trade_size != 0) {
        SendOrder(instrument, trade_size);
    }
}

void CombinedStrategy::SendOrder(const Instrument* instrument, int trade_size) {
    double price = trade_size > 0 ? instrument->top_quote().bid() + aggressiveness_
                                  : instrument->top_quote().ask() - aggressiveness_;

    OrderParams params(*instrument, abs(trade_size), price,
                       MARKET_CENTER_ID_NASDAQ,
                       trade_size > 0 ? ORDER_SIDE_BUY : ORDER_SIDE_SELL,
                       ORDER_TIF_DAY, ORDER_TYPE_LIMIT);

    trade_actions()->SendNewOrder(params);
}
