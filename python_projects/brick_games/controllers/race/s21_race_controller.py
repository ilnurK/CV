"""The module implements the racing game controller

- sys and os: adding game logic module to the system path
- s21_race: game logic module
"""

from typing import List
import sys
import os
file_path = os.path.abspath(__file__)
file_directory = os.path.dirname(file_path)
module_path: str = file_directory + "/../../brick_game/race/"
sys.path.append(module_path)
from s21_race import FSM, RaceStates, Directions # noqa: 402


class RaceController():
    """Race game controller logic

    Arguments
    ---------
    __fsm: FSM
        Finite state machine of a racing game
    """

    def __init__(self):
        """The controller initialization"""
        self.__fsm: FSM = FSM()

    def set_state(self, state: RaceStates, key=None) -> RaceStates:
        """Set the FSM state

        Parameters
        ----------
        state : RaceStates
            The given state
        key : Directions, optional
            The given direction, by default None

        Returns
        -------
        RaceStates
            Transition result
        """

        return self.__fsm.set_state(state, key=key)

    def get_state(self) -> RaceStates:
        """Get the FSM state

        Returns
        -------
        RaceStates
            The current fsm state
        """

        return self.__fsm.state

    def get_field(self) -> List[List[str]]:
        """Get the field of game

        Returns
        -------
        List[List[str]]
            2D char matrix
        """

        return self.__fsm.body[::-1]

    def get_score(self) -> int:
        """Returns the score of game

        Returns
        -------
        int
            The game score
        """

        return self.__fsm.score

    def get_highscore(self) -> int:
        """Returns the high score of game

        Returns
        -------
        int
            The game high score
        """

        return self.__fsm.highscore

    def get_level(self) -> int:
        """Returns the level of game

        Returns
        -------
        int
            The game level
        """

        return self.__fsm.speed

    def get_speed(self, delay) -> int:
        """Returns the speed of game

        Returns
        -------
        int
            The game speed
        """

        return self.__fsm.speed_kmh(delay)

    def set_highscore(self, value: int) -> None:
        """Sets the game high score

        Parameters
        ----------
        value : int
            The given score
        """

        self.__fsm.set_highscore(value)

    def write_highscore(self):
        """Calling fsm's write highscore when state == GAME_OVER"""

        self.__fsm.write_highscore()

    def is_filled_cell(self, symbol: str) -> bool:
        """Is given symbol not an empty

        Parameters
        ----------
        symbol : str
            The symbol being checked

        Returns
        -------
        bool
            The comparasion result
        """

        return (symbol == self.__fsm.car.symbol) or (
                symbol == self.__fsm.field.border)

    def is_extra_info(self) -> bool:
        """Does the controller have an extra field

        Returns
        -------
        bool
            The extra field availability
        """

        return False

    @property
    def win_state(self) -> RaceStates:
        """Returns the win state value

        Returns
        -------
        RaceStates
            The win state value
        """

        return RaceStates.WIN

    @property
    def game_over_state(self) -> RaceStates:
        """Returns the game over state value

        Returns
        -------
        RaceStates
            The game over state value
        """

        return RaceStates.GAME_OVER

    def show(self) -> None:
        """Helper function for showing the game field"""
        return self.__fsm.show()
