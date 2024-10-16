from feature import Feature 
class FeatureManager:
    
    def __init__(self):
        self.__feature_list = []
        
    def add_feature(self,feature:Feature)->None:
        self.__feature_list.append(feature)
    
    def remove_feature_by_key(self, name: str) -> None:
        self.__feature_list = [f for f in self.__feature_list if f.name != name]
    
    def get_feature_by_key(self, name: str) -> Feature | None:
        for feature in self.__feature_list:
            if feature.name == name:
                return feature
        return None
        
        
    
    def get_feature_list(self):
        return self.__feature_list

        