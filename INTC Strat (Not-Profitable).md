# Introduction

The objective of this report is to evaluate the performance of a trading strategy implemented using the Strategy Studio platform. This strategy employs two core technical indicators, **VWAP (Volume Weighted Average Price)** and **Bollinger Bands**, to make automated trading decisions. The strategy buys or sells based on the price's position relative to these indicators, aiming to capture profitable opportunities when markets are volatile. The strategy is fully automated and tracks real-time price and volume data to make decisions.

The performance of this strategy is assessed using real trading data, which includes executed orders, price data, and cumulative profit and loss over time. The goal is to understand how effectively the strategy performs in various market conditions and evaluate the strategy's overall profitability, trade execution, and adherence to its intended trading logic.

---

# Strategy Overview

The strategy is built on the foundation of two primary technical indicators: **VWAP** and **Bollinger Bands**.

### VWAP

The VWAP is a price indicator that accounts for both price and volume, offering an average price weighted by volume over a defined period. It provides a sense of the "fair" market value based on trading activity. The strategy uses VWAP to compare the current price of an instrument to its average price, identifying whether the instrument is undervalued or overvalued relative to market activity.

### Bollinger Bands

Bollinger Bands are volatility indicators that consist of:
- A middle band (the simple moving average).
- Two outer bands (set a specific number of standard deviations above and below the moving average).

The bands expand or contract based on market volatility, offering a measure of price range and potential overbought or oversold conditions. The strategy uses these bands to trigger buy or sell signals when the price crosses these thresholds.

---

# Trading Logic and Execution

The strategy utilizes the **VWAPBollinger** class to monitor price and volume data of instruments and make trading decisions. The core trading logic is built around the following principles:

- **Position Size and Aggressiveness**: 
  - The position size determines the number of units bought or sold (default: 100 units).
  - The aggressiveness factor adjusts the limit order price to increase execution likelihood.

- **Buy Signal**: A buy signal is triggered when:
  - Price falls below the lower Bollinger Band.
  - Price is also below the VWAP.

- **Sell Signal**: A sell signal occurs when:
  - Price rises above the upper Bollinger Band.
  - Price is also above the VWAP.

- **Portfolio Adjustment**: The strategy rebalances based on signals, calculating and executing orders to match the target portfolio size.

---

# Key Parameters

1. **Position Size**: Default is 100 units, adjustable based on risk tolerance.
2. **Aggressiveness**: Adjusts limit order prices for quicker execution in volatile markets.

---

# Performance Evaluation

Key metrics for evaluating the strategy include:

### Cumulative Profit and Loss (PnL)
Tracks the overall profitability of the strategy over time.

Cumulative PnL over Time
<img width="773" alt="image" src="https://github.com/user-attachments/assets/2b5355e6-b6cb-4429-8966-6ebf7dea22f9" />


### Order Frequency
Analyzes trading activity across different times of day.

<img width="717" alt="image" src="https://github.com/user-attachments/assets/6195ef91-ab01-484c-af85-a37815bbef7d" />


### Trade Execution Analysis
Compares trade prices with VWAP and Bollinger Bands to evaluate adherence to trading rules.

Trade Prices vs. Bollinger Bands
<img width="733" alt="image" src="https://github.com/user-attachments/assets/1a508694-4f8c-45a1-8391-017fe7358450" />


---

# Conclusion

The strategy uses VWAP and Bollinger Bands to identify overbought and oversold conditions. While the strategy captures trends effectively, further optimizations (e.g., position sizing, slippage management) could enhance performance in varied market environments.
