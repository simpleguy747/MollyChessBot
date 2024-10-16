from typing import Self

class Feature:
    def __init__(self, feature: dict[str, str | float]) -> None:
        """
        Initialize a Feature object.

        Args:
        feature (dict[str, str | float]): A dictionary with "FeatureName" and "FeatureValue" keys.
        """
        if "FeatureName" not in feature or "FeatureValue" not in feature:
            raise ValueError("Feature dictionary must have 'FeatureName' and 'FeatureValue' keys")
        if not isinstance(feature["FeatureName"], str):
            raise ValueError("Feature name must be a string")
        if not isinstance(feature["FeatureValue"], (int, float)):
            raise ValueError("Feature value must be numeric")
        self._feature: dict[str, float] = {feature["FeatureName"]: float(feature["FeatureValue"])}

    @property
    def name(self) -> str:
        """Get the feature name."""
        return list(self._feature.keys())[0]

    @property
    def value(self) -> float:
        """Get the feature value."""
        return list(self._feature.values())[0]

    def __repr__(self) -> str:
        return f"Feature({self.name}={self.value})"
