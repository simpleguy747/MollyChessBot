from feature import Feature
from feature_manager import FeatureManager

class EvalTransformer:
    
    def __init__(self,featureManager:FeatureManager):
        self.__featureManager = featureManager
    
    def transform_eval(self):
        feature_weights = self.set_material_weights()
        return feature_weights
    
    
    def set_material_weights(self):
        
        mg_material_weight_pawn = self.__featureManager.get_feature_by_key("MG_MATERIAL_PAWN")
        mg_material_weight_knight = self.__featureManager.get_feature_by_key("MG_MATERIAL_PAWN")
        mg_material_weight_bishop = self.__featureManager.get_feature_by_key("MG_MATERIAL_PAWN")
        mg_material_weight_rook = self.__featureManager.get_feature_by_key("MG_MATERIAL_PAWN")
        mg_material_weight_queen = self.__featureManager.get_feature_by_key("MG_MATERIAL_PAWN")
        
        eg_material_weight_pawn = self.__featureManager.get_feature_by_key("EG_MATERIAL_PAWN")
        eg_material_weight_knight = self.__featureManager.get_feature_by_key("EG_MATERIAL_PAWN")
        eg_material_weight_bishop = self.__featureManager.get_feature_by_key("EG_MATERIAL_PAWN")
        eg_material_weight_rook = self.__featureManager.get_feature_by_key("EG_MATERIAL_PAWN")
        eg_material_weight_queen = self.__featureManager.get_feature_by_key("EG_MATERIAL_PAWN")
        
        return {"MG_MATERIAL":[0,mg_material_weight_pawn.value,
                 mg_material_weight_knight.value,
                 mg_material_weight_bishop.value,
                 mg_material_weight_rook.value,
                 mg_material_weight_queen.value,0],
                
                "EG_MATERIAL":[0,eg_material_weight_pawn.value,
                 eg_material_weight_knight.value,
                 eg_material_weight_bishop.value,
                 eg_material_weight_rook.value,
                 eg_material_weight_queen.value,0]}
        
        