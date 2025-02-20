"""The module implements the tetris game controller

- ctypes: used to load a C DLL library that contains functions for
initializing the game and saving high scores.
- IntEnum: defines finite state machine (FSM) states and game errors
- sys and os: adding game logic module to the system path
- get_dll_path: to get the path where the game logic DLL is located
"""

import ctypes
from enum import IntEnum
import sys
import os
from typing import List, Tuple
cur_file: str = os.path.abspath(__file__)
rel_path: str = "/../../brick_game/"
sys.path.append(os.path.dirname(cur_file) + rel_path)
from race.s21_race import get_dll_path  # noqa: E402


class S21Figure(ctypes.Structure):
    """S21Figure C structure"""
    pass


class S21Field(ctypes.Structure):
    """S21Field C structure"""
    pass


class S21TetrisFSM(ctypes.Structure):
    """S21TetrisFSM C structure

    Describes Finite state machine of tetris game
    """

    _fields_ = [('field', ctypes.POINTER(S21Field)),
                ('cur_figure', ctypes.POINTER(S21Figure)),
                ('next_figure', ctypes.POINTER(S21Figure)),
                ('score', ctypes.c_size_t),
                ('highscore', ctypes.c_size_t),
                ('level', ctypes.c_size_t),
                ('shifts_counter', ctypes.c_size_t),
                ('state', ctypes.c_int)]


class S21TetrisCController(ctypes.Structure):
    """S21TetrisCController C structure

    Describes tetris game controller
    """

    _fields_ = [('fsm', ctypes.POINTER(S21TetrisFSM)),
                ('height', ctypes.c_size_t),
                ('width', ctypes.c_size_t),
                ('fig_len', ctypes.c_size_t),
                ('fig_symb', ctypes.c_char),
                ('field_symb_fill', ctypes.c_char),
                ('field_symb_fig', ctypes.c_char)]


class S21TetrisError(IntEnum):
    """Game errors"""
    NULL_ERROR = 0
    BAD_ALLOC = 1
    PATH_ERROR = 2


class S21TetrisStates(IntEnum):
    """FSM states"""
    NULL_STATE = 0
    START = 1
    SPAWN = 2
    MOVING = 3
    SHIFTING = 4
    ATTACHING = 5
    GAME_OVER = 6
    WIN = -1


class S21XYPair(ctypes.Structure):
    """S21XYPair C structure, that descripes 2D point"""
    _fields_ = [('x', ctypes.c_int),
                ('y', ctypes.c_int)]


class TetrisPyController():
    """Tetris python game controller logic

    Arguments
    ---------
    __rel_path: str
        The relative path from s21_race module to game logic C DLL
    __lib_name:str
        The game logic C DLL name
    __lib: ctypes.CDLL
        The loaded DLL
    __error_code: ctypes.c_int
        The error status
    ctrl_ptr: ctypes.POINTER(S21TetrisCController)
        The pointer to S21TetrisCController
    ctrl: S21TetrisCController
        The S21TetrisCController instance
    state: S21TetrisStates
        The current state of FSM
    field: List[List[str]]
        The 2D matrix - field of game
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
        self.__rel_path: str = "/../../obj/controllers/tetris/"
        self.__lib_name: str = "libtetris.so"
        self.__lib: ctypes.CDLL = ctypes.CDLL(get_dll_path(
            self.__rel_path, self.__lib_name))

        self.__lib.InitTetrisController.restype = ctypes.POINTER(
            S21TetrisCController)
        self.__lib.InitTetrisController.argtypes = [ctypes.POINTER(
            ctypes.c_int)]
        self.__error_code = ctypes.c_int()
        self.ctrl_ptr = self.__lib.InitTetrisController(ctypes.byref(
            self.__error_code))
        self.ctrl = self.ctrl_ptr.contents
        if self.__error_code.value != S21TetrisError.NULL_ERROR:
            raise RuntimeError("Incorrect tetris py controller initialization")

        self.state: S21TetrisStates = S21TetrisStates.START
        self.__lib.SetTetrisState.restype = ctypes.c_int
        self.__lib.SetTetrisState.argtypes = [
            ctypes.POINTER(S21TetrisCController),
            ctypes.c_int,
            ctypes.c_int,
            ctypes.POINTER(ctypes.c_int)]

        self.field: List[List[str]] = []
        self.__lib.GetFieldAt.restype = ctypes.c_char_p
        self.__lib.GetFieldAt.argtypes = [
            ctypes.POINTER(S21TetrisCController), S21XYPair]

        self.next: List[Tuple[int, int]] = []
        self.__lib.GetExtraInfoAt.restype = S21XYPair
        self.__lib.GetExtraInfoAt.argtypes = [
            ctypes.POINTER(S21TetrisCController),
            ctypes.c_int
        ]

        self.score: int = 0
        self.__lib.GetTetrisScore.restype = ctypes.c_size_t
        self.__lib.GetTetrisScore.argtypes = [
            ctypes.POINTER(S21TetrisCController)]

        self.highscore: int = 0
        self.__lib.GetTetrisHighScore.restype = ctypes.c_size_t
        self.__lib.GetTetrisHighScore.argtypes = [
            ctypes.POINTER(S21TetrisCController)]

        self.level: int = 0
        self.__lib.GetTetrisLevel.restype = ctypes.c_size_t
        self.__lib.GetTetrisLevel.argtypes = [
            ctypes.POINTER(S21TetrisCController)]

        self.__lib.DeleteController.restype = None
        self.__lib.DeleteController.argtypes = [ctypes.POINTER(
            S21TetrisCController)]

    def set_state(self, state: int, dir: int) -> S21TetrisStates:
        """Set the FSM state

        Parameters
        ----------
        state : int
            The given state
        dir : int
            The given direction

        Returns
        -------
        S21TetrisStates
            Transition result

        Raises
        ------
        RuntimeError
            If error_code is not NULL_ERROR
        """

        self.state = self.__lib.SetTetrisState(
            self.ctrl_ptr,
            ctypes.c_int(state),
            ctypes.c_int(dir),
            ctypes.byref(self.__error_code))
        if self.__error_code.value != S21TetrisError.NULL_ERROR:
            raise RuntimeError("Incorrect tetris py controller initialization")
        return self.state

    def get_field(self) -> List[List[str]]:
        """Get the field of game

        Returns
        -------
        List[List[str]]
            2D char matrix
        """

        rows: int = self.ctrl.height
        cols: int = self.ctrl.width
        field: List[List[str]] = [
            [' ' for _ in range(cols)] for _ in range(rows)]
        for i in range(rows):
            for j in range(cols):
                xy = S21XYPair(x=j, y=i)
                char = self.__lib.GetFieldAt(self.ctrl_ptr, xy)
                if char:
                    field[i][j] = char.decode('utf-8')[0]
        self.field = field
        return field

    def is_extra_info(self):
        """Does the controller have an extra field

        Returns
        -------
        bool
            The extra field availability
        """

        return True

    def get_extra_info(self) -> List[Tuple[int, int]]:
        """Get extra info list

        Returns
        -------
        List[Tuple[int, int]]
            List of coordinates
        """

        rows: int = self.ctrl.fig_len
        info: List[S21XYPair] = []
        for i in range(rows):
            info.append(self.__lib.GetExtraInfoAt(self.ctrl_ptr,
                                                  ctypes.c_int(i)))
        self.next = [(c.x, c.y) for c in info]
        return self.next

    def get_score(self):
        """Returns the score of game

        Returns
        -------
        int
            The game score
        """

        self.score = self.__lib.GetTetrisScore(self.ctrl_ptr)
        return self.score

    def get_highscore(self):
        """Returns the high score of game

        Returns
        -------
        int
            The game high score
        """

        self.highscore = self.__lib.GetTetrisHighScore(self.ctrl_ptr)
        return self.highscore

    def get_level(self):
        """Returns the level of game

        Returns
        -------
        int
            The game level
        """

        self.level = self.__lib.GetTetrisLevel(self.ctrl_ptr)
        return self.level

    def __del__(self):
        """Freeing memory by S21TetrisCController pointer"""
        self.__lib.DeleteController(self.ctrl_ptr)
