class DataManager:
    def __init__(self) -> None:
        pass
    
    def load_data_fen(self,path):
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

            fen_position_and_actual_result = {"fen_position":fen_position,"actual_result":actual_result}
            fen_positions_and_actual_results.append(fen_position_and_actual_result)

        return fen_positions_and_actual_results