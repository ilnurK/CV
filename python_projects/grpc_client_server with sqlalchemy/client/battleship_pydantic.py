"""The module contains a class for validating the protobuf message

The module requires pydantic library just for validating message
parameters, json module - to get constraints dictionary to check,
os - to get DATA_DIR environment variable
"""

from pydantic import BaseModel, Field, model_validator
from typing import List, Dict, Any


class Battleship(BaseModel):
    """Pydantic class for validate protobuf battleship message

    Attributes
    ----------
    alignment : str
        The alignment of the battleship
    name : str
        The name of the battleship
    ship_class : str
        The class of the battleship
    length : float
        The length of the battleship
    crew_size : int
        The size of the crew on the battleship
    armed : bool
        Indicates if the battleship is armed
    officers : List[Dict[str, str]]
        A list representing the officers message class

    Methods
    -------
    model_validator(mode='after')
        A method decorator for performing model validation
    validate_args(self) -> Any
        A method that implements parameter checking
    """

    alignment: str
    name: str
    ship_class: str = Field(alias='class')
    length: float
    crew_size: int
    armed: bool
    officers: List[Dict[str, str]]
    constraints: Dict[str, Dict[str, str]]

    @model_validator(mode='after')
    def validate_args(self) -> Any:
        """A method that implements parameter checking

        Raises
        ------
        ValueError
            If any attribute does not fit to constraints
        """
        ship_class: str = self.ship_class
        ship_constraints: Dict[str, str] = self.constraints[ship_class]

        length: float = self.length
        length_range = ship_constraints['length']
        lower, higher = (float(c) for c in length_range.split('-'))
        if length > higher or length < lower:
            raise ValueError("length incorrect")

        crew_size: int = self.crew_size
        crew_range = ship_constraints['crew_size']
        lower, higher = (int(c) for c in crew_range.split('-'))
        if crew_size > higher or crew_size < lower:
            raise ValueError("crew size incorrect")

        armed = self.armed
        if ship_constraints['can_armed'] == 'Yes':
            can_armed = True
        else:
            can_armed = False
        if armed and not can_armed:
            raise ValueError("armed status incorrect")

        alignment = self.alignment
        if ship_constraints['can_hostile'] == 'Yes':
            can_hostile = True
        else:
            can_hostile = False
        if alignment == 'Enemy' and not can_hostile:
            raise ValueError("alignment incorrect")
        if alignment == 'Ally' and self.name == 'Unknown':
            raise ValueError("ally battleship name could not be Unknown")
