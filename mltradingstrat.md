# FIN556 Trading Model: High-Frequency Trading using Reinforcement Learning and Transformers

## Overview

This project implements a high-frequency trading (HFT) strategy using modern deep learning techniques, including transformer models and reinforcement learning (RL). The aim is to predict mid-price changes in financial data and optimize trading decisions using a policy-gradient-based reinforcement learning approach. The system simulates a trading environment to evaluate the strategies and performance.

## Key Components

### 1. Data Collection

- **Source:** Yahoo Finance API (`yfinance` library).
- **Frequency:** 1-minute interval data.
- **Preprocessing:**
  - Sorting data by datetime.
  - Filling missing values.
  - Creating features like `mid_price` (average of High and Low prices).
  - Standardizing data using `StandardScaler` from `scikit-learn`.

### 2. Feature Engineering

- **Extracted Features:**
  - Open, High, Low, Close, Volume, and `mid_price`.
- **Generated Inputs and Targets for the Model:**
  - Sliding windows of 100 timesteps (1-minute data).
  - Predicted the next `mid_price` value.

### 3. Modeling

#### Transformer Model

- **Architecture:**
  - Input features are embedded using a linear layer.
  - Transformer encoder with:
    - 2 layers
    - 4 attention heads
    - Feedforward dimension of 64
    - Dropout of 0.1
  - Final layer predicts the next mid-price.
- **Loss Function:** Mean Squared Error (MSE).
- **Optimizer:** Adam with a learning rate of 1e-4.

### 4. Reinforcement Learning

#### Trading Environment

- **Simulates a trading environment using predicted and actual price changes.**
- **States:**
  - Difference between predicted and actual price changes.
- **Actions:**
  - `-1` (short), `0` (flat), and `1` (long).
- **Reward:**
  - Change in portfolio value based on the action taken.

#### Policy Network

- **Architecture:**
  - **Input:** Predicted price movement.
  - **Hidden layer:** 16 neurons with ReLU activation.
  - **Output:** Logits for actions `[-1, 0, 1]`.
- **Training:**
  - Policy Gradient method.
  - Discount factor γ = 0.99.
  - Model checkpointing every 100 episodes.

### 5. Evaluation

- **Metrics:**
  - Mean Squared Error (MSE) for the Transformer model's predictions.
  - Final portfolio profit for the reinforcement learning policy.
- **Visualization:**
  - Predicted vs. actual mid-price changes.
  - Training progress with profit trends.
  
  Final Portfolio Profit Trends <img width="833" alt="image" src="https://github.com/user-attachments/assets/38fb3e41-98ba-45c6-9dce-9d69497c8b05" />


## Installation

### Prerequisites

- **Python:** 3.8+
- **Required Libraries:**
  - `torch`, `torchvision`, `torchaudio`
  - `numpy`, `pandas`
  - `matplotlib`, `seaborn`
  - `scikit-learn`, `yfinance`
  - `dpkt`, `tqdm`

### Steps

1. **Clone the repository:**

    ```bash
    git clone https://github.com/atharvanaik10/FIN-556-Final/blob/main/fin556trading.ipynb
    cd fin556trading
    ```

2. **Install the required packages:**

    ```bash
    pip install -r requirements.txt
    ```

3. **Run the script:**

    ```bash
    python main.py
    ```

## Usage

### Data Collection

Modify the ticker, start date, and end date in the `download_data` function to fetch your desired dataset.

### Training the Transformer Model

Train the model to predict mid-price changes:


### Reinforcement Learning

Train the RL agent:


## Results

### Transformer Model

- Achieved MSE on test data: ~1.999.

### Reinforcement Learning

- Trained over 10,000 episodes with checkpointing.
- Final portfolio profit trends improve with episodes.

---
