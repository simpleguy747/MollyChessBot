from feature import Feature 
from feature_manager import FeatureManager
from eval_transformer import EvalTransformer
from eval_manager import EvalManager
from data_manager import DataManager

import chess
import math
import concurrent.futures

class Tuner:
    
    def __init__(self):
        self.__data_path = "/home/gb/My/MollyChessBot/tuner/data-files/quiet-labeled.v7.epd"
        self.__FM = FeatureManager()
        self.__ET = EvalTransformer(self.__FM)
        self.__EM = EvalManager()
        self.__DM = DataManager()
    
    def add_features(self):
        self.__FM.add_feature(Feature({"FeatureName":"MG_MATERIAL_PAWN", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"MG_MATERIAL_KNIGHT", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"MG_MATERIAL_BISHOP", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"MG_MATERIAL_ROOK", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"MG_MATERIAL_QUEEN", "FeatureValue":900}))
        
        self.__FM.add_feature(Feature({"FeatureName":"EG_MATERIAL_PAWN", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"EG_MATERIAL_KNIGHT", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"EG_MATERIAL_BISHOP", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"EG_MATERIAL_ROOK", "FeatureValue":900}))
        self.__FM.add_feature(Feature({"FeatureName":"EG_MATERIAL_QUEEN", "FeatureValue":900}))
    
    # def transform_eval(self):
    #     self.__feature_weights = self.__ET.transform_eval()
        
        
    def setup_board(self, fen:str):
        board = chess.Board(fen)
        return board

 
        
    def compute_sigmoid(self,eval):
        scale_factor = 1.0/400
        sigmoid =  1 / (1 + math.exp(-eval*scale_factor))
        return sigmoid
    
    # def compute_error(self):
    #     fen_positions_and_actual_results = self.__DM.load_data_fen(self.__data_path)
    #     number_of_positions = len(fen_positions_and_actual_results)
    #     mse_error = 0.0

    #     with concurrent.futures.ThreadPoolExecutor(max_workers=4) as executor:
    #         futures = []
    #         for single_position_with_result in fen_positions_and_actual_results:
    #             futures.append(executor.submit(self.process_position, single_position_with_result))
            
    #         print('here')
    #         for future in concurrent.futures.as_completed(futures):
    #             evaluation_score_normalized, actual_result = future.result()
    #             mse_error += pow(evaluation_score_normalized - actual_result, 2)

    #     return (mse_error/number_of_positions)
        
    # def process_position(self, single_position_with_result):
    #     board = self.setup_board(single_position_with_result['fen_position'])
    #     actual_result = single_position_with_result['actual_result']
    #     evaluation_score = self.__EM.compute_eval(board, self.__feature_weights)
    #     evaluation_score_normalized = self.compute_sigmoid(evaluation_score)
    #     return evaluation_score_normalized, actual_result
    
    def compute_error(self,fen_positions_and_actual_results,eval_weights):
        
        number_of_positions = len(fen_positions_and_actual_results)
        mse_error = 0.0
        
        for single_position_with_result in fen_positions_and_actual_results:
            board = self.setup_board(single_position_with_result['fen_position'])
            actual_result=single_position_with_result['actual_result']
        
            evaluation_score = self.__EM.compute_eval(board,eval_weights)
            evaluation_score_normalized = self.compute_sigmoid(evaluation_score)
            mse_error += pow(evaluation_score_normalized - actual_result, 2)

        return (mse_error/number_of_positions)


    def tune(self):
        
        
        material_val = self.__ET.transform_eval()
        fen_positions_and_actual_results = self.__DM.load_data_fen(self.__data_path)
        number_of_params_to_tune = len(material_val)
        
        print(f"number_of_params_to_tune = {len(self.__FM.get_feature_list())}")
        print(f"material_val = {material_val}")
        
        best_params=material_val.copy()
        step_direction = 1
        is_improving = True
        best_mse=self.compute_error(fen_positions_and_actual_results,best_params)
        print(f"Initial MSE = {best_mse}")
        
        improving_index = 0
        while is_improving:
            is_improving = False
            improving_index = improving_index + 1
            print(f"started iteration :  {improving_index}, {best_params}")
            for weight_index in range(0,number_of_params_to_tune-1):
                new_params = best_params.copy()
                print(new_params)
                new_params[weight_index] += step_direction
                new_mse = self.compute_error(fen_positions_and_actual_results,new_params)

                print(f'parameter under consideration {parameter_dictionary[weight_index]} error is {new_mse} for value {new_params[weight_index]}')
                    
                if new_mse < best_mse:
                    best_mse = new_mse
                    best_params = new_params.copy()
                    is_improving = True
                    print(f'Improved parameter {parameter_dictionary[weight_index]} with step +{step_direction}')

                else:
                    new_params[weight_index] -= 2*step_direction
                    new_mse = self.compute_error(fen_positions_and_actual_results,new_params)

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




t = Tuner()
DM = DataManager()
t.add_features()
t.tune()