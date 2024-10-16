import chess

class EvalManager:
    def __init__(self) -> None:
        self.__gamePhaseInc = [0,0,1,1,2,4,0]
        
        
    def compute_eval(self, board, eval_features):
        eval = 0
        game_phase = 0
        
        mg_material_values = eval_features['MG_MATERIAL']
        eg_material_values = eval_features['EG_MATERIAL']
        
        mg_material_eval = [0,0]
        eg_material_eval = [0,0]
        
        for sq in range(0,64):
            piece = board.piece_at(sq)
            if piece:
                
                piece_type = piece.piece_type
                piece_color = piece.color
                
                game_phase += self.__gamePhaseInc[piece_type]
                
                mg_material_eval[piece_color]+=mg_material_values[piece_type]
                eg_material_eval[piece_color]+=eg_material_values[piece_type]
            
        
         # tapered eval
        mgScore = mg_material_eval[chess.WHITE] - mg_material_eval[chess.BLACK]
        egScore = eg_material_eval[chess.WHITE] - eg_material_eval[chess.BLACK]
        
        mgPhase = game_phase
        
        if mgPhase > 24:
            mgPhase = 24; # in case of early promotion
        
        egPhase = 24 - mgPhase
        
        eval = (mgScore * mgPhase + egScore * egPhase) / 24

        return eval
    
    