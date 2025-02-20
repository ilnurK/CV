"""Brick Games server component for client-server game architecture

- annotations: required for forward declarations within the module.
of non-player characters (NPCs).
- fastapi: asynchronous web framework - server base
- pydantic: validating requests and responses
- IntEnum: defining available games
- logging: capturing server statuses in the terminal
- sys and os: adding game controller modules to the system path
- race.s21_race_controller: adding race game controller with game
commands and states
- tetris.s21_tetris_controller: adding tetris game controller and states
- snake.s21_snake_controller: adding snake game controller and states
"""

from __future__ import annotations
from fastapi import FastAPI, HTTPException, Path
from fastapi.responses import JSONResponse
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from enum import IntEnum
import logging
import sys
import os
from typing import List, Union, Optional, Tuple
cur_module: str = os.path.abspath(__file__)
rel_path: str = "/../../controllers/"
module_path: str = os.path.dirname(cur_module) + rel_path
sys.path.append(module_path)
from race.s21_race_controller import (  # noqa: E402
    RaceController, Directions, RaceStates)
from tetris.s21_tetris_controller import (  # noqa: E402
    TetrisPyController, S21TetrisStates
)
from snake.s21_snake_controller import (  # noqa: E402
    SnakePyController, SnakeStates
)

app = FastAPI(root_path='/api')

dirs = Directions

logger = logging.getLogger('uvicorn.error')


class PrintToLogger:
    """Overrides stdout.write to output logs"""

    def write(self, message: str):
        """Writes an informational message to the logging instance

        Parameters
        ----------
        message : str
            The info message
        """

        logger.debug(message)


sys.sdtdout = PrintToLogger


class GamesList(BaseModel):
    """Schema contains array of GameInfo

    Arguments
    ---------
    games: List[GameInfo] - The array of GameInfo
    """

    games: List[GameInfo]


class GameInfo(BaseModel):
    """Schema that contain id and name of game

    Arguments
    ---------
    id: int - The ID of game
    name: str - The name of game
    """

    id: int
    name: str


class UserAction(BaseModel):
    """Schema contains users act and playing status

    Arguments
    ---------
    action_id: int - The ID action
    hold: bool - indicates button holding
    are_playing: bool - indicate playing or being in menu
    """

    action_id: int
    hold: bool
    are_playing: bool


class GameState(BaseModel):
    """Schema describing the game state,
    including the game field as a 2D array.

    Arguments
    ---------
    field: List[List[str]] - The matrix of game's field
    next: List[Tuple[int, int]] - The matrix of extra field
    score: int - The current score of game
    high_score: int - The maximum score of game
    level: int - The level of game
    speed: int - The speed of game
    pause: bool - The pause status
    """

    field: List[List[str]] = [[]]
    next: List[Tuple[int, int]] = []
    score: int = 0
    high_score: int = 0
    level: int = 0
    speed: int = 0
    pause: bool = False
    state: int = 0
    delay: int = 0


class ErrorMessage(BaseModel):
    """Schema contains the server's message error

    Arguments
    ---------
    message: str - The error message
    """

    message: str


class Games(IntEnum):
    """Available Games enumeration"""
    Race = 1
    Snake = 2,
    Tetris = 3,


class ServerController():
    """Common controller for available games

    Attributes
    ----------
    cur_game_id: int
        The enumerated identifier representing the current game in play
    ctrl: Union[RaceController, TetrisPyController, SnakePyController]
        The instance of the current game controller
    state: Union[RaceStates, S21TetrisStates, SnakeStates]
        The current state of the game's finite state machine (FSM)
    next: List[Tuple[int, int]]
        A list of coordinates representing the next figure in the
        Tetris game
    dir: dirs
        The current command direction being executed in the game
    dir_hold: bool
        The flag indicating whether a button is being held down,
        affecting the direction status
    std_delay: int
        The initial delay period between FSM state transitions
    std_delay_step: int
        The decremental step value for the delay when a new level
        is achieved
    delay: int
        The current delay duration influencing game state transitions
    pause: bool
        The flag indicating whether the game is currently paused
    score: int
        The current score that the player has accumulated in the game
    high_score: int
        The highest score achieved in the game
    level: int
        The current level that the player has reached in the game
    speed: int
        The speed value for the racing game
    """

    def __init__(self, ctrl: Union[RaceController, TetrisPyController,
                                   SnakePyController]):
        """The common server controller initialization

        Parameters
        ----------
        ctrl : Union[RaceController, TetrisPyController, SnakePyController]
             The instance of the current game controller
        """

        self.cur_game_id = 0
        self.ctrl: Union[RaceController,
                         TetrisPyController,
                         SnakePyController] = ctrl
        self.state: Union[RaceStates, S21TetrisStates, SnakeStates]
        self.field: List[List[str]] = self.ctrl.get_field()
        self.next: List[Tuple[int, int]] = self.init_next()
        self.dir: dirs = dirs.NULL_DIR
        self.dir_hold: bool = False
        self.std_delay: int = 600
        self.std_delay_step: int = 50
        self.delay: int = self.std_delay
        self.pause: bool = False

        self.score: int = self.ctrl.get_score()
        self.high_score: int = self.ctrl.get_highscore()
        self.level: int = self.ctrl.get_level()
        self.speed: int = self.init_speed(self.std_delay)

    def init_next(self) -> List[Tuple[int, int]]:
        """Next figure initialization

        Returns
        -------
        List[Tuple[int, int]]
            A list of coordinates representing the next figure
        """

        res: List[List[Tuple[int, int]]] = []
        if self.ctrl.is_extra_info():
            res = self.ctrl.get_extra_info()
        return res

    def init_speed(self, delay: int) -> int:
        """The speed of game attribute initialization

        Parameters
        ----------
        delay : int
            The delay period between FSM transitions, ms

        Returns
        -------
        int
            The speed value
        """

        speed: int = 0
        if hasattr(self.ctrl, "get_speed"):
            speed = self.ctrl.get_speed(delay)
        return speed

    def update_values(self):
        """Update game attributes after FSM transition"""
        self.field = self.ctrl.get_field()
        self.next = self.init_next()

        self.score = self.ctrl.get_score()
        self.high_score = self.ctrl.get_highscore()
        self.level = self.ctrl.get_level()

        self.delay = self.std_delay - self.level * self.std_delay_step
        self.speed = self.init_speed(self.delay)


SC: Optional[ServerController] = None

GamesListData: List[GameInfo] = [
    GameInfo(id=Games.Tetris, name="Tetris"),
    GameInfo(id=Games.Snake, name="Snake"),
    GameInfo(id=Games.Race, name="Race"),
]


app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5500", "http://127.0.0.1:5500"],
    allow_credentials=True,
    allow_methods=["*"],  # allow all methods
    allow_headers=["*"],  # allow all headers
)


@app.get('/games', response_model=Union[GamesList, ErrorMessage])
def get_games() -> Union[GamesList, ErrorMessage]:
    """Getting the list of games

    Returns
    -------
    Union[GamesList, ErrorMessage]
        The GamesList schema or error message

    Raises
    ------
    HTTPException 500
        If the GamesListData did not set
    """

    if GamesListData:
        return GamesList(games=GamesListData)
    else:
        raise HTTPException(status_code=500,
                            detail="Ошибка сервера. Игры не найдены")


@app.post('/games/{game_id}', response_model=Union[str, ErrorMessage])
async def set_game(game_id: int = Path(...)) -> Union[str, ErrorMessage]:
    """Choosing the specified game

    Parameters
    ----------
    game_id : int, optional
        The game enumerate identification, by default Path(...)

    Returns
    -------
    Union[str, ErrorMessage]
        Success or error log message

    Raises
    ------
    HTTPException 409
        If the game is already in progress
    HTTPException 404
        If the game_id is incorrect
    HTTPException 500
        If the game controller has not been initialized
    """

    global SC
    if SC and game_id == SC.cur_game_id:
        raise HTTPException(status_code=409, detail=(
            "Пользователь уже запустил другую игру"))
    game = next((g for g in GamesListData if g.id == game_id), None)
    if game is None:
        raise HTTPException(status_code=404, detail=(
            "Игра с заданным идентификатором не найдена"))
    if game_id == Games.Race:
        SC = ServerController(RaceController())
        SC.state = RaceStates.START
    elif game_id == Games.Tetris:
        SC = ServerController(TetrisPyController())
        SC.state = S21TetrisStates.START
    elif game_id == Games.Snake:
        SC = ServerController(SnakePyController())
        SC.state = SnakeStates.START
    if SC is None:
        raise HTTPException(status_code=500, detail=(
            "Ошибка сервера. Неудачная инициализация игры"
        ))
    SC.cur_game_id = game_id
    return "Игра запущена"


@app.get('/games/reset', response_model=str)
async def reset_game() -> str:
    """Resets the game controller

    Returns
    -------
    str
        The log message
    """

    global SC
    SC = None
    return "Игра сброшена"


@app.post('/actions', response_model=Union[str, ErrorMessage])
def set_action(action: UserAction) -> Union[str, ErrorMessage]:
    """Set game command

    Parameters
    ----------
    action : UserAction
        The schema contains game direction and hold status

    Returns
    -------
    Union[str, ErrorMessage]
        Success or error log message

    Raises
    ------
    HTTPException 500
        If the game controller has not been initialized
    HTTPException 400
        If the game was not set or incorrect request's game command
    """

    if action.are_playing:
        if SC is None:
            raise HTTPException(status_code=500, detail=(
                                "Ошибка сервера. Контроллер не загружен"))
        if not SC.cur_game_id:
            raise HTTPException(status_code=400, detail=(
                "Пользователь не запустил игру"
            ))
        try:
            SC.dir_hold = action.hold
            if action.hold:
                SC.dir = action.action_id
                if SC.dir == dirs.PAUSE:
                    SC.pause = not SC.pause
                if SC.cur_game_id == Games.Tetris and (
                        SC.dir == dirs.DOWN or SC.dir == dirs.ACTION):
                    SC.dir_hold = False
        except AttributeError:
            raise HTTPException(status_code=400, detail=(
                "Ошибка в теле запроса"))
    return "Действие выполнено"


@app.get('/state', response_model=Union[GameState, ErrorMessage])
def get_state() -> Union[GameState, ErrorMessage]:
    """Getting the game state schema

    Returns
    -------
    Union[GameState, ErrorMessage]
        Schema or error log message

    Raises
    ------
    HTTPException 500
        If the game controller has not been initialized or
        game was not set
    """

    if SC is None or not SC.cur_game_id:
        raise HTTPException(status_code=500,
                            detail="Ошибка сервера. Игра не задана")
    SC.update_values()
    return make_state()


def make_state() -> GameState:
    """Makes GameState schema from controller attributes

    Returns
    -------
    GameState
        The game state describe schema
    """

    gs: GameState = GameState()
    for attr, val in vars(SC).items():
        if hasattr(gs, attr):
            setattr(gs, attr, val)
    return gs


@app.post('/state/{state_id}', response_model=Union[GameState, ErrorMessage])
def set_state(state_id: int = Path(...)):
    """Getting the list of games

    Parameters
    ----------
    state_id : int, optional
        _description_, by default Path(...)

    Returns
    -------
    _type_
        _description_

    Raises
    ------
    HTTPException 500
        If the game controller has not been initialized or
        game was not set or set_state raise error
    """

    if SC is None or not SC.cur_game_id:
        raise HTTPException(status_code=500,
                            detail="Ошибка сервера. Игра не задана")
    try:
        SC.state = SC.ctrl.set_state(state_id, SC.dir)
        SC.update_values()
        if ((SC.dir == dirs.ACTION and SC.cur_game_id == Games.Snake)
                or (SC.dir == dirs.UP and SC.cur_game_id == Games.Race)):
            SC.delay //= 5
            SC.speed = SC.init_speed(SC.delay)
        if not SC.dir_hold:
            SC.dir = dirs.NULL_DIR

    except Exception:
        raise HTTPException(status_code=500,
                            detail="Ошибка сервера. Ошибка в обработке")
    return make_state()


@app.exception_handler(HTTPException)
async def http_exception_handler(request, e: HTTPException) -> JSONResponse:
    """Managing error message

    Parameters
    ----------
    request
        The request object
    e : HTTPException
        The raised exception

    Returns
    -------
    JSONResponse
        Response generated using the ErrorMessage scheme
    """

    error_message = ErrorMessage(message=e.detail)
    return JSONResponse(
        status_code=e.status_code,
        content=error_message.model_dump()
    )

if __name__ == '__main__':
    import uvicorn
    uvicorn.run(app, port=8080)
