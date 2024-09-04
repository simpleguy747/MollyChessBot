import chess
import numpy as np
import time
from datetime import datetime
import math

piece_types = {
    'P': 'Pawn',
    'N': 'Knight',
    'B': 'Bishop',
    'R': 'Rook',
    'Q': 'Queen',
    'K': 'King'
}

def set_board(fen_position):
    board = chess.Board(fen_position)
    return board

def evaluate_board(material_array,material_val):
    eval = 0
    for index in range(0,len(material_array[0])):
        eval+=material_val[index] * len(material_array[0][index])

    for index in range(0,len(material_array[1])):
        eval-=material_val[index] * len(material_array[1][index])

    return eval/100

def material_count_arr(board):
   # Initialize empty lists for each piece type
    material_arr_white = [[], [], [], [], [], []]  # For white pieces
    material_arr_black = [[], [], [], [], [], []]  # For black pieces

    # Piece types
    piece_types = [chess.PAWN, chess.KNIGHT, chess.BISHOP, chess.ROOK, chess.QUEEN, chess.KING]

    # Iterate over all squares
    for sq in range(64):
        piece = board.piece_at(sq)
        if piece:
            if piece.color == chess.WHITE:
                material_arr_white[piece_types.index(piece.piece_type)].append(sq)
            else:
                material_arr_black[piece_types.index(piece.piece_type)].append(sq)

    
    return [material_arr_white,material_arr_black]
   
    



def sigmoid(eval):
  return 1 / (1 + math.exp(-eval))

def compute_errors(fen_positions_and_actual_results,material_eval):

    number_of_positions = len(fen_positions_and_actual_results)
    mse_error = 0.0
    for single_position_with_result in fen_positions_and_actual_results:
        material_count = single_position_with_result['material_count_array']
        actual_result=single_position_with_result['actual_result']
       
        evaluation_score = evaluate_board(material_count,material_eval)
        evaluation_score_normalized = sigmoid(evaluation_score)
        mse_error += pow(evaluation_score_normalized - actual_result, 2)

    return (mse_error/number_of_positions)    


def load_data_fen(path):
    fen_positions_and_actual_results =[]
    
    with open(path, 'r') as file:
        fens_and_results = [line.strip() for line in file.readlines()]

    for fen_and_result in fens_and_results:
        fen_position,fen_result =fen_and_result.split('c9')
        fen_position = fen_position.strip()
        fen_result = fen_result.replace('"','').replace(";",'').strip()
        actual_result = 0.5
        if fen_result == "1-0":
            actual_result = 1
        elif fen_result == "0-1":
            actual_result = 0

        board = chess.Board(fen_position)
        material_count_array=material_count_arr(board)
        fen_position_and_actual_result = {"material_count_array":material_count_array,"actual_result":actual_result}
        fen_positions_and_actual_results.append(fen_position_and_actual_result)

    return fen_positions_and_actual_results



def tune(fen_positions_and_actual_results,material_val):
    number_of_params_to_tune = len(material_val)
    best_params=material_val.copy()
    step_direction = 1
    is_improving = True
    best_mse=compute_errors(fen_positions_and_actual_results,best_params)
    print(f"Initial MSE = {best_mse}")
    improving_index = 0
    while is_improving:
        is_improving = False
        improving_index = improving_index + 1
        print(f"started iteration :  {improving_index}, {best_params}")
        for weight_index in range(0,number_of_params_to_tune-1):
            new_params = best_params.copy()

            new_params[weight_index] += step_direction
            new_mse = compute_errors(fen_positions_and_actual_results,new_params)

            print(f'parameter under consideration {parameter_dictionary[weight_index]} error is {new_mse} for value {new_params[weight_index]}')
                
            if new_mse < best_mse:
                best_mse = new_mse
                best_params = new_params.copy()
                is_improving = True
                print(f'Improved parameter {parameter_dictionary[weight_index]} with step +{step_direction}')

            else:
                new_params[weight_index] -= 2*step_direction
                new_mse = compute_errors(fen_positions_and_actual_results,new_params)

                print(f'parameter under consideration {parameter_dictionary[weight_index]} error is {new_mse} for value {new_params[weight_index]}')
                
                if new_mse < best_mse:
                    best_mse = new_mse
                    best_params = new_params.copy()
                    is_improving = True
                    print(f'Improved parameter {parameter_dictionary[weight_index]} with step -{step_direction}')
        
        # print(best_params)
        # if (improving_index % 10) == 0:
        print(f"ended iteration :  {improving_index}, {best_params}")
    return best_params




parameter_dictionary = ["Pawn","Knight","Bishop","Rook","Queen","King"]
material_val = [900,900,900,900,900,900]

path="quiet-labeled.epd"
fen_positions_and_actual_results = load_data_fen(path)
print("positions loaded")
best_material_params = tune(fen_positions_and_actual_results,material_val)

print("==============================================")
print(best_material_params)

# [87, 291, 307, 454, 902, 900]