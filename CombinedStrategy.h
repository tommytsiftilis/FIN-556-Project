/*================================================================================
*     Source: ../RCM/StrategyStudio/examples/strategies/CombinedStrategy/CombinedStrategy.h
*================================================================================*/

#pragma once

#ifndef _STRATEGY_STUDIO_LIB_EXAMPLES_COMBINED_STRATEGY_H_
#define _STRATEGY_STUDIO_LIB_EXAMPLES_COMBINED_STRATEGY_H_

#ifdef _WIN32
    #define _STRATEGY_EXPORTS __declspec(dllexport)
#else
    #ifndef _STRATEGY_EXPORTS
    #define _STRATEGY_EXPORTS
    #endif
#endif

#include <Strategy.h>
#include <Analytics/ScalarRollingWindow.h>
#include <MarketModels/Instrument.h>
#include <vector>
#include <map>
#include <iostream>

using namespace RCM::StrategyStudio;

class VWAPBollinger {
public:
    VWAPBollinger(int window_size = 20, double multiplier = 2.0)
        : price_window_(window_size), volume_window_(window_size), multiplier_(multiplier) {}

    void Update(double price, double volume) {
        price_window_.push_back(price);
        volume_window_.push_back(price * volume);
    }

    double VWAP() const {
        return price_window_.Sum() > 0 ? volume_window_.Sum() / price_window_.Sum() : 0.0;
    }

    double UpperBand() const {
        return price_window_.Mean() + multiplier_ * price_window_.StdDev();
    }

    double LowerBand() const {
        return price_window_.Mean() - multiplier_ * price_window_.StdDev();
    }

    bool FullyInitialized() const { return price_window_.full(); }

private:
    Analytics::ScalarRollingWindow<double> price_window_;
    Analytics::ScalarRollingWindow<double> volume_window_;
    double multiplier_;
};

class CombinedStrategy : public Strategy {
public:
    CombinedStrategy(StrategyID strategyID, const std::string& strategyName, const std::string& groupName);
    ~CombinedStrategy();

    virtual void OnBar(const BarEventMsg& msg);
    virtual void OnResetStrategyState();
    virtual void DefineStrategyParams();
    virtual void RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate);

private:
    void AdjustPortfolio(const Instrument* instrument, int desired_position);
    void SendOrder(const Instrument* instrument, int trade_size);

private:
    boost::unordered_map<const Instrument*, VWAPBollinger> vwap_bollinger_map_;
    int position_size_;
    double aggressiveness_;
};

extern "C" {
    _STRATEGY_EXPORTS const char* GetType() { return "CombinedStrategy"; }

    _STRATEGY_EXPORTS IStrategy* CreateStrategy(const char* strategyType, unsigned strategyID,
                                                const char* strategyName, const char* groupName) {
        if (strcmp(strategyType, GetType()) == 0) {
            return new CombinedStrategy(strategyID, strategyName, groupName);
        }
        return nullptr;
    }

    _STRATEGY_EXPORTS const char* GetAuthor() { return "Group6"; }
    _STRATEGY_EXPORTS const char* GetAuthorGroup() { return "DefaultGroup"; }
    _STRATEGY_EXPORTS const char* GetReleaseVersion() { return Strategy::release_version(); }
}

#endif
