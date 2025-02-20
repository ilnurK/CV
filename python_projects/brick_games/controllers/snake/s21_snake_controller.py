"""The module implements the snake game controller

- ctypes: used to load a C DLL library that contains functions for
initializing the game and saving high scores.
- IntEnum: defines finite state machine (FSM) states
- sys and os: adding game logic module to the system path
- get_dll_path: to get the path where the game logic DLL is located
"""

import ctypes
from enum import IntEnum
import sys
import os
from typing import List
cur_file: str = os.path.abspath(__file__)
rel_path: str = "/../../brick_game/"
sys.path.append(os.path.dirname(cur_file) + rel_path)
from race.s21_race import get_dll_path  # noqa: E402


class SnakeStates(IntEnum):
    """FSM states"""
    NULL_STATE = 0
    START = 1
    MOVING = 2
    SHIFTING = 3
    EATING = 4
    GROWING = 5
    COLLIDED = 6
    GAME_OVER = 7
    WIN = -1


class SnakePyController():
    """Tetris python game controller logic

    Arguments
    ---------
    __rel_path: str
        The relative path from s21_race module to game logic C DLL
    __lib_name:str
        The game logic C DLL name
    lib: ctypes.CDLL
        The loaded DLL
    ctrl_ptr: ctypes.POINTER(c_void_p)
        The pointer to S21SnakeCController
    height: int
        The field's height
    field: List[List[str]]
        The 2D matrix - field of game
    width: int
        The field's width
    state: SnakeStates
        The current state of FSM
    next: List[Tuple[int, int]]
        The list of next figure coordinates
    score: int
        The score of game
    highscore: int
        The high score of game
    level: int
        The level of game
    """

    def __init__(self):
        """The controller initialization"""
        self.__rel_path: str = "/../../obj/controllers/snake/"
        self.__lib_name: str = "libsnake.so"
        self.lib = ctypes.CDLL(get_dll_path(self.__rel_path, self.__lib_name))

        self.lib.GetSnakeController.restype = ctypes.POINTER(ctypes.c_void_p)
        self.lib.GetSnakeController.argtypes = []
        self.ctrl_ptr = self.lib.GetSnakeController()
        if not self.ctrl_ptr:
            raise RuntimeError("Incorrect snake py controller initialization")

        self.lib.GetSnakeFieldHeight.restype = ctypes.c_size_t
        self.lib.GetSnakeFieldWidth.restype = ctypes.c_size_t
        self.lib.GetSnakeFieldHeight.argtypes = [ctypes.POINTER(
            ctypes.c_void_p)]
        self.lib.GetSnakeFieldWidth.argtypes = [ctypes.POINTER(
            ctypes.c_void_p)]

        self.state: int = 1  # == SnakeStates.START
        self.lib.SetSnakeState.restype = ctypes.c_int

        self.lib.SetSnakeState.argtypes = [ctypes.POINTER(ctypes.c_void_p),
                                           ctypes.c_int, ctypes.c_int]

        self.field: List[List[str]] = []
        self.height: int = self.lib.GetSnakeFieldHeight(self.ctrl_ptr)
        self.width: int = self.lib.GetSnakeFieldWidth(self.ctrl_ptr)
        self.lib.GetSnakeFieldAt.restype = ctypes.c_char
        self.lib.GetSnakeFieldAt.argtypes = [ctypes.POINTER(ctypes.c_void_p),
                                             ctypes.c_int, ctypes.c_int]

        self.score: int = 0
        self.lib.GetSnakeScore.restype = ctypes.c_size_t
        self.lib.GetSnakeScore.argtypes = [ctypes.POINTER(ctypes.c_void_p)]

        self.highscore: int = 0
        self.lib.GetSnakeHighScore.restype = ctypes.c_size_t
        self.lib.GetSnakeHighScore.argtypes = [ctypes.POINTER(ctypes.c_void_p)]

        self.level: int = 0
        self.lib.GetSnakeLevel.restype = ctypes.c_size_t
        self.lib.GetSnakeLevel.argtypes = [ctypes.POINTER(ctypes.c_void_p)]

        self.lib.DeleteSnakeController.restype = None
        self.lib.DeleteSnakeController.argtypes = [ctypes.POINTER(
            ctypes.c_void_p)]

    def set_state(self, state: int, dir: int) -> int:
        """Set the FSM state

        Parameters
        ----------
        state : int
            The given state
        dir : int
            The given direction

        Returns
        -------
        int
            Transition result
        """

        self.state = self.lib.SetSnakeState(self.ctrl_ptr,
                                            ctypes.c_int(state),
                                            ctypes.c_int(dir))
        return self.state

    def get_field(self) -> List[List[str]]:
        """Get the field of game

        Returns
        -------
        List[List[str]]
            2D char matrix
        """

        self.field: List[List[str]] = [
            ([self.lib.GetSnakeFieldAt(self.ctrl_ptr, ctypes.c_int(x),
                                       ctypes.c_int(y)).decode('utf-8')[0]
             for x in range(self.width)]) for y in range(self.height)]
        return self.field

    def is_extra_info(self):
        """Does the controller have an extra field

        Returns
        -------
        bool
            The extra field availability
        """

        return False

    def get_score(self) -> int:
        """Returns the score of game

        Returns
        -------
        int
            The game score
        """

        self.score = self.lib.GetSnakeScore(self.ctrl_ptr)
        return self.score

    def get_highscore(self) -> int:
        """Returns the high score of game

        Returns
        -------
        int
            The game high score
        """

        self.highscore = self.lib.GetSnakeHighScore(self.ctrl_ptr)
        return self.highscore

    def get_level(self) -> int:
        """Returns the level of game

        Returns
        -------
        int
            The game level
        """

        self.level = self.lib.GetSnakeLevel(self.ctrl_ptr)
        return self.level

    def __del__(self):
        """Freeing memory by S21SnakeCController pointer"""
        self.lib.DeleteSnakeController(self.ctrl_ptr)
