import pandas as pd
import numpy as np
import math

def load_data(path):
    return pd.read_csv(path)

def evaluate(row, material_weights):
    white_counts = np.array([
        row["white_pawns_count"], 
        row["white_knights_count"], 
        row["white_bishops_count"], 
        row["white_rooks_count"], 
        row["white_queens_count"]
    ])
    black_counts = np.array([
        row["black_pawns_count"], 
        row["black_knights_count"], 
        row["black_bishops_count"], 
        row["black_rooks_count"], 
        row["black_queens_count"]
    ])
    piece_differences = white_counts - black_counts
    eval_score = np.dot(piece_differences, material_weights)
    return eval_score / 100

def sigmoid_value(evaluation_score):
    return 1 / (1 + np.exp(-evaluation_score))

def compute_gradient(df, material_weights, learning_rate, batch_size, gradient_squared_sum, momentum, velocity):
    num_samples = len(df)
    indices = np.arange(num_samples)
    np.random.shuffle(indices)
    mse = 0
    
    for start_idx in range(0, num_samples, batch_size):
        end_idx = min(start_idx + batch_size, num_samples)
        batch_indices = indices[start_idx:end_idx]
        batch_df = df.iloc[batch_indices]

        gradients = np.zeros(len(material_weights))
        for _, row in batch_df.iterrows():
            eval_score = evaluate(row, material_weights)
            sigmoid_eval = sigmoid_value(eval_score)
            actual_result = float(row["actual_result"])
            mse += (sigmoid_eval - actual_result) ** 2
            error_derivative = 2 * (sigmoid_eval - actual_result)
            piece_differences = np.array([
                row["white_pawns_count"] - row["black_pawns_count"],
                row["white_knights_count"] - row["black_knights_count"],
                row["white_bishops_count"] - row["black_bishops_count"],
                row["white_rooks_count"] - row["black_rooks_count"],
                row["white_queens_count"] - row["black_queens_count"]
            ])
            gradients += error_derivative * sigmoid_eval * (1 - sigmoid_eval) * piece_differences
        
        gradients /= len(batch_df)
        gradient_squared_sum += gradients ** 2
        adjusted_gradients = gradients / np.sqrt(gradient_squared_sum)
        
        # Momentum update
        velocity = momentum * velocity + learning_rate * adjusted_gradients
        material_weights -= velocity

    return mse / num_samples, material_weights, gradient_squared_sum, velocity

path = "quiet-labeled.epd.csv"
# initial_material_weights = np.array([99.33303418, 563.12042364, 581.85920428, 766.87695887, 1521.34873543], dtype=float)
initial_material_weights = np.array([900,900,900,900,900],dtype=float)
learning_rate = 0.1
batch_size = 100
momentum = 0.9
df = load_data(path)

material_weights = initial_material_weights.copy()
old_mse = float('inf')
improving = True
iterator = 0
gradient_squared_sum = np.zeros(len(material_weights))
velocity = np.zeros(len(material_weights))

while improving:
    iterator += 1
    mse, material_weights, gradient_squared_sum, velocity = compute_gradient(
        df, material_weights, learning_rate, batch_size, gradient_squared_sum, momentum, velocity
    )
    
    if old_mse > mse:
        old_mse = mse
        improving = True
        best = "best"
    else:
        improving = False
        best = ""

    print(f"{iterator}. MSE: {mse:.6f}, weights: {material_weights} {best}")

    # MSE: 0.072713, weights: [ 87.37599225 292.94836527 309.50735592 456.83567609 909.3030963 ]