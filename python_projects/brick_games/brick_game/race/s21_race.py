"""The module implements the brick games racing game

- annotations: required for forward declarations within the module.
- deepcopy: for 2d array full copy,
- deque: utilized for creating a complete copy of 2D arrays.
- random: implements a queue for managing the spawning and deletion
of non-player characters (NPCs).
- ctypes: used to load a C DLL library that contains functions for
initializing the game and saving high scores.
- IntEnum: defines finite state machine (FSM) states and commands
within the game
"""

from __future__ import annotations
from copy import deepcopy
from collections import deque
import random as r
import ctypes
import os
from enum import IntEnum
from typing import List, Dict, Tuple, Optional, Deque, Any  # noqa: 402


def get_dll_path(rel_path: str, dll_name: str) -> str:
    """Retrieves the relative DLL path from the specified module

    Parameters
    ----------
    rel_path : str
        the relative path from file to library
    dll_name : str
        library name

    Returns
    -------
    str
        The whole path
    """

    cur_path: str = os.path.abspath(__file__)
    dll_path: str = os.path.dirname(cur_path) + rel_path + dll_name
    return dll_path


class Directions(IntEnum):
    """Game commands"""
    NULL_DIR = 0,
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4
    ACTION = 5,
    PAUSE = 6


dirs = Directions


class RaceStates(IntEnum):
    """FSM states"""
    NULL_STATE = 0
    START = 1
    DRIVE = 2
    CHANGE_LANES = 3
    OVERTAKE = 4
    COLLISION = 5
    GAME_OVER = 6
    WIN = -1


class Point():
    """Point in two-dimensional space

    Attributes
    ----------
    x: int
        The x coordinate of point
    y: int
        The y coordinate of point
    """

    def __init__(self, x=None, y=None, other=None, other_shift=None) -> None:
        """Inits point class

        Parameters
        ----------
        x : int, optional
            The x coordinate of point, by default 0
        y : int, optional
            The y coordinate of point, by default 0
        other : Point, optional
            The other point, by default None
        other_shift : str, optional
            The offset from a given point, by default None

        Raises
        ------
        ValueError
            If given arguments are incorrects
        """

        if x is not None and y is not None:
            self.x = x
            self.y = y
        elif other and type(other) is Point:
            self.x = other.x
            self.y = other.y
            if other_shift == "up":
                self.y += 1
            elif other_shift == "down":
                self.y -= 1
            elif other_shift == "left":
                self.x -= 1
            elif other_shift == "right":
                self.x += 1
            elif other_shift:
                raise ValueError("incorrect other_shift parameter")
        elif other and type(other) is not Point:
            raise ValueError("incorrect other type")
        else:
            self.x = 0
            self.y = 0

    def __eq__(self, other: Point) -> bool:
        """Condition of equality between two points

        Parameters
        ----------
        other : Point
            The comparasion point

        Returns
        -------
        bool
            True, if points have the same coordinates
        """

        return self.x == other.x and self.y == other.y


class Car():
    """A two-dimensional car with geometric and speed parameters

    Attributes
    ----------
    __width: int
        The width of the car
    __height: int
        The height of the car
    __length: int
        The length of the car
    __top: Point
        The highest point of the car
    __body:  List[Point]
        The car body geometry
    __symbol: str
        The car body symbol
    """

    __width: int = 3
    __height: int = 4
    __length: int = 7

    def __init__(self, top: Point) -> None:
        """Inits car class

        Parameters
        ----------
        __top: Point
            The highest point of the car
        """

        self.__top: Point = top
        self.__body: List[Point] = [Point() for _ in range(self.__length)]
        self.move(self.top)
        self.__symbol: str = '0'

    @classmethod
    def cls_width(cls) -> int:
        """Returns the width of cars

        Returns
        -------
        int
            The width of car
        """

        return cls.__width

    @classmethod
    def cls_height(cls) -> int:
        """Returns the height of cars

        Returns
        -------
        int
            The height of car
        """

        return cls.__height

    @property
    def symbol(self) -> str:
        """Return the car's symbol

        Returns
        -------
        str
            The symbol of car
        """

        return self.__symbol

    @property
    def body(self) -> List[Point]:
        """Returns the car's points

        Returns
        -------
        List[Point]
            The points that make up a car
        """

        return self.__body

    @property
    def top(self) -> Point:
        """The top point of the car

        Returns
        -------
        Point
            The highest point of the car
        """

        return self.__top

    def move(self, top: Point) -> None:
        """Builds car body from top point

         0
        000
         0
        0 0

        Parameters
        ----------
        top : Point
            Top point of car
        """

        self.__body[0].x, self.__body[0].y = top.x, top.y
        self.__body[1].x, self.__body[1].y = top.x, top.y - 1
        self.__body[2].x, self.__body[2].y = top.x - 1, top.y - 1
        self.__body[3].x, self.__body[3].y = top.x + 1, top.y - 1
        self.__body[4].x, self.__body[4].y = top.x, top.y - 2
        self.__body[5].x, self.__body[5].y = top.x - 1, top.y - 3
        self.__body[6].x, self.__body[6].y = top.x + 1, top.y - 3

    def downward(self, value=1) -> None:
        """Moves the car down by a given value

        Parameters
        ----------
        value : int, optional
            The specified y-coordinate offset value, by default 1
        """

        self.top.y -= value
        self.move(top=self.top)


class Field():
    """2d array - the field along which the car moves

    Attributes
    ----------
    __width: int
        The width of the field
    __height: int
        The height of the height
    __road: str
        The symbol of road
    __border: str
        The symbol of obstacles
    __border_fill: int
        The counter of board fill pattern
    __border_free: int
        The counter of board free pattern
    __borders_y: List[int]
        The list of pattern ordinates
    __body: List[List[int]]
        The 2d array for field
    """

    def __init__(self) -> None:
        """Field class initialization"""
        self.__width: int = 10
        self.__height: int = 20
        self.__road: str = ' '
        self.__border: str = '#'
        self.__border_fill: int = 3
        self.__border_free: int = 1
        self.__borders_y: List[int] = self.__get_border_indexes()
        self.__body: List[List[str]] = [[self.__filler_condition(
            y, x) for x in range(self.__width)] for y in range(self.__height)]

    @property
    def width(self) -> int:
        """Returns the width of field

        Returns
        -------
        int
            The field's width
        """

        return self.__width

    @property
    def height(self) -> int:
        """Returns the height of field

        Returns
        -------
        int
            The field's height
        """

        return self.__height

    @property
    def body(self) -> List[List[str]]:
        """Returns the height of field

        Returns
        -------
        int
            The field's height
        """

        return self.__body

    @property
    def road(self) -> str:
        """Returns the symbol of road

        Returns
        -------
        str
            The road's symbol
        """

        return self.__road

    @property
    def border(self) -> str:
        """Returns the symbol of border

        Returns
        -------
        str
            The border's symbol
        """

        return self.__border

    @property
    def border_pattern(self) -> Tuple[int, int]:
        """Returns the border pattern

        Returns
        -------
        Tuple[int, int]
            The counter of fill pattern, the counter of free pattern
        """

        return self.__border_fill, self.__border_free

    def __get_border_indexes(self) -> List[int]:
        """Gets array's ordinates where the borders are

        Returns
        -------
        List[int]
            Ordinate border indexes
        """

        borders_y: List[int] = []
        cr_fill: int = 0
        cr_free: int = 0
        cur_symbol: str = self.__border
        for i in range(self.__height):
            if cur_symbol == self.__border:
                if cr_fill >= self.__border_fill:
                    cr_fill = 0
                    cr_free = 1
                    cur_symbol = self.__road
                else:
                    cr_fill += 1
            elif cur_symbol == self.__road:
                if cr_free >= self.__border_free:
                    cr_free = 0
                    cr_fill = 1
                    cur_symbol = self.__border
                else:
                    cr_free += 1
            borders_y.append(i) if cur_symbol == self.__border else None
        return borders_y

    def __filler_condition(self, y: int, x: int) -> str:
        """Check array's y and x to fill it

        Parameters
        ----------
        y : int
            _description_
        x : int
            _description_

        Returns
        -------
        str
            Filler symbol
        """

        symbol: str = self.__road
        if ((x == 0 or x == self.__width - 1) and y in self.__borders_y):
            symbol = self.__border
        return symbol

    def shift_downward(self) -> None:
        """Release all cells down"""
        for y in range(self.__height):
            for x in range(self.__width):
                self.__fill_downward_cell(y, x)

    def __fill_downward_cell(self, y: int, x: int) -> None:
        """Fills the cell in the array below it in a row

        Parameters
        ----------
        y : int
            The row of array
        x : int
            The column of array
        """

        if y > 0:
            self.__body[y - 1][x] = self.__body[y][x]
        if y == self.__height - 1 and (x == 0 or x == self.__width - 1):
            i: int = y - 1
            cr: int = 0
            if self.__body[y][x] == self.__border:
                while self.__body[i][x] == self.__border and i > - 1:
                    cr += 1
                    i -= 1
                if cr == self.__border_fill:
                    self.__body[y][x] = self.__road
            elif self.__body[y][x] == self.__road:
                while self.__body[i][x] == self.__road and i > -1:
                    cr += 1
                    i -= 1
                if cr == self.__border_free:
                    self.__body[y][x] = self.__border

    def place_car(self, car: Car, is_hero_car=False) -> None:
        """Place the given car to array

         0
        000
         0
        0 0

        Parameters
        ----------
        car : Car
            The given car
        is_hero_car : bool, optional
            NPC or hero car, by default False
        """

        for p in car.body:
            if is_hero_car and self.__body[p.y][p.x] != self.__road:
                raise RuntimeError("collision")
            check_y: bool = p.y > -1 and p.y < self.height
            check_x: bool = p.x > -1 and p.x < self.width
            if check_y and check_x:
                self.__body[p.y][p.x] = car.symbol

    def show(self):
        """Shows field"""
        for y in range(self.__height - 1, -1, -1):
            for x in range(self.__width):
                print(self.__body[y][x], end='')
            print()


class FSM():
    """Finite state machine of a racing game

    Attributes
    ----------
    __state: RaceStates
        The state of game
    __speed: int
        The game's level
    __speed_limit: int
        The game's maximum level
    __score: int
        Current game score
    __rel_path: str
        Path to highscore handle c library
    __lib_name: str
        The c library to handle highscore
    __lib_hscore: ctypes.CDLL
        The loaded highscore c dll
    __highscore: int
        The game's highscore obtained from higscore file
    __road: Field
        The empty road field with borders
    __field: Field
        The road with placed cars
    __width: int
        The width of field
    __height: int
        The height of field
    __car: Car
        The car of player
    __delay_to_npc: int
        Time until next NPC spawn
    __npcs: Deque[Car]
        The NPC's car deque
    __overtake_increment: int
        The number of NPCs you need to overtake to get one point
    __key: Optional[dirs]
        Specified command for FSM
    __stable_states: List[RaceStates]
        Thе list of states that do not transition into others by themselves
    """

    def __init__(self) -> None:
        """FSM class initialization"""
        self.__state: RaceStates = RaceStates.START
        self.__speed: int = 1
        self.__speed_limit: int = 10
        self.__score: int = 0
        self.__rel_path: str = "/../../obj/brick_game/"
        self.__lib_name: str = "libhighscore.so"
        self.lib_hscore: ctypes.CDLL = ctypes.CDLL(get_dll_path(
            self.__rel_path, self.__lib_name))
        self.__highscore: int = self.read_highscore()
        self.__road: Field = Field()
        self.__field: Field = Field()
        self.__width: int = self.__road.width
        self.__height: int = self.__road.height
        self.__car: Car = Car(Point(x=0, y=0))
        self.__delay_to_npc: int = 0
        self.__npcs: Deque[Car] = deque()
        self.__overtake_increment: int = 5
        self.__key: Optional[dirs] = None
        self.__stable_states: List[RaceStates] = [RaceStates.DRIVE,
                                                  RaceStates.GAME_OVER]

    @property
    def state(self) -> RaceStates:
        """Returns FSM state

        Returns
        -------
        RaceStates
            The FSM state
        """

        return self.__state

    @state.setter
    def state(self, value: RaceStates):
        """Set FSM state as property

        Parameters
        ----------
        value : RaceStates
            The game state

        Raises
        ------
        ValueError
            if incorrect state value
        """

        if value < 0 or value > max(RaceStates, key=lambda v: v.value):
            raise ValueError("incorrect state value")
        self.__state = value

    @property
    def speed(self) -> int:
        """Returns race game level

        Returns
        -------
        int
            The level of game
        """

        return self.__speed

    @speed.setter
    def speed(self, value: int) -> None:
        """Set the game level

        Parameters
        ----------
        value : int
            The level value

        Raises
        ------
        ValueError
            If the value negative or greater than level limit
        """

        if value < 0 or value > self.__speed_limit:
            raise ValueError("incorrect speed value")
        self.__speed = value

    def speed_kmh(self, delay: int) -> int:
        """Returns speed as the inverse of delay

        Parameters
        ----------
        delay : int
            Delay between states in ms

        Returns
        -------
        int
            speed in km/h
        """

        return (3600 // delay) * 6

    @property
    def score(self) -> int:
        """Returns game score

        Returns
        -------
        int
            The score of game
        """

        return self.__score

    @score.setter
    def score(self, value: int) -> None:
        """Set game score

        Parameters
        ----------
        value : int
            The given score

        Raises
        ------
        ValueError
            If negative value
        """

        if value < 0:
            raise ValueError("incorrect score value")
        self.__score = value

    @property
    def highscore(self) -> int:
        """Get game highscore

        Returns
        -------
        int
            The highscore of game
        """

        return self.__highscore

    @property
    def npcs(self) -> Deque[Car]:
        """Returns the deque of NPCs

        Returns
        -------
        Deque[Car]
            The NPCs deque
        """

        return self.__npcs

    @property
    def body(self) -> List[List[str]]:
        """Returns the array of field

        Returns
        -------
        List[List[str]]
            the 2d array of FSM field
        """

        return self.__field.body

    @property
    def height(self) -> int:
        """Returns the FSM field's height

        Returns
        -------
        int
            The height of FSM field
        """

        return self.__height

    @property
    def width(self) -> int:
        """Returns the FSM field's width

        Returns
        -------
        int
            The width of FSM field
        """

        return self.__width

    @property
    def car(self) -> Car:
        """Returns the player's car

        Returns
        -------
        Car
            The car of game's player
        """

        return self.__car

    @property
    def field(self) -> Field:
        """Returns the FSM's field

        Returns
        -------
        Field
            The field of fsm
        """

        return self.__field

    def set_state(self, state: RaceStates,
                  key=None, init_data=None) -> RaceStates:
        """Set the FSM state and returns the next stable state

        Parameters
        ----------
        state : RaceStates
            The given state
        key : dirs, optional
            The given direction, by default None
        init_data : Dict[str, Any], optional
            Initialization dictionary for tests, by default None

        Returns
        -------
        RaceStates
            The stable state
        """

        self.state = state
        state_out: RaceStates = self.unstable_state(key=key,
                                                    init_data=init_data)
        while state_out not in self.__stable_states:
            state_out = self.unstable_state(key, init_data)
            if key:
                key = None
        return state_out

    def unstable_state(self, key=None, init_data=None) -> RaceStates:
        """Returns the next unstable state based on the current state

        Parameters
        ----------
        key : dirs, optional
            _description_, by default None
        init_data : Dict[str, Any], optional
           Initialization dictionary for tests, by default None

        Returns
        -------
        RaceStates
            The unstable state
        """

        self.__field = deepcopy(self.__road)
        if key:
            self.__key_handle(key)
        if self.state == RaceStates.DRIVE:
            self.__drive_handle(init_data)
        elif self.state == RaceStates.CHANGE_LANES:
            self.__shift_handle()
        elif self.state == RaceStates.OVERTAKE:
            self.__overtake_handle()
        elif self.state == RaceStates.COLLISION:
            self.__collision_handle()
        elif self.state == RaceStates.START:
            self.__start_handle(init_data)
        self.__field.place_car(self.__car)
        self.__place_npcs()
        return self.state

    def __key_handle(self, key: dirs) -> None:
        """Checks given keys and set CHANGE_LANES state

        Parameters
        ----------
        key : dirs
            given key
        """

        if key in [dirs.LEFT, dirs.RIGHT]:
            self.state = RaceStates.CHANGE_LANES
            self.__key = key

    def __start_handle(self, init_data: Optional[Dict[str, Any]]) -> None:
        """Managing the start state

        Parameters
        ----------
        init_data : Optional[Dict[str, Any]]
           Initialization dictionary for tests, by default None
        """

        self.state = RaceStates.DRIVE
        init_side: Optional[str] = None
        if init_data and init_data.get("hero_side", None) is not None:
            init_side = init_data["hero_side"]
        self.__car = self.car_init(Car.cls_height() - 1, init_side=init_side)
        if init_data and init_data.get("duration_to_npc", None) is not None:
            self.__delay_to_npc = init_data["duration_to_npc"]
        else:
            max_delay_to_wait_npc: int = 8
            self.__delay_to_npc = r.randint(0, max_delay_to_wait_npc)

    def car_init(self, y: int, init_side="right") -> Car:
        """Initialization of Player and NPC car

        Parameters
        ----------
        y : int
            The row of field
        init_side : str, optional
            The left or the right side of field, by default right

        Returns
        -------
        Car
            The initializated car
        """

        if init_side:
            is_left_init: int = 1 if init_side == "left" else 0
        else:
            is_left_init = r.randint(0, 1)
        if is_left_init:
            x: int = Car.cls_width()
        else:
            x = self.__field.width - Car.cls_width() - 1
        return Car(Point(x=x, y=y))

    def read_highscore(self) -> int:
        """Reads highscore from file using dll

        Returns
        -------
        int
            read highscore

        Raises
        ------
        Exception
            If the file is not opened correctly
        """

        self.lib_hscore.S21InitHighScore.argtypes = (
            ctypes.c_char_p, ctypes.POINTER(ctypes.c_bool))
        self.lib_hscore.S21InitHighScore.restype = ctypes.c_size_t

        self.lib_hscore.S21GetRaceLogFileName.restype = ctypes.c_char_p
        file_name = self.lib_hscore.S21GetRaceLogFileName()

        is_creating_error = ctypes.c_bool()
        score = self.lib_hscore.S21InitHighScore(file_name, ctypes.byref(
            is_creating_error))
        if is_creating_error.value:
            raise Exception("incorrect init highscore")
        return score

    def write_highscore(self) -> None:
        """Writes highscore to file using dll

        Raises
        ------
        Exception
            If the file is not opened correctly
        """

        self.lib_hscore.S21WriteHighScore.argtypes = (
            ctypes.c_char_p, ctypes.c_int)
        self.lib_hscore.S21WriteHighScore.restype = ctypes.c_bool

        self.lib_hscore.S21GetRaceLogFileName.restype = ctypes.c_char_p
        file_name = self.lib_hscore.S21GetRaceLogFileName()

        chighscores: int = ctypes.c_int(self.__highscore)
        is_writing_error = self.lib_hscore.S21WriteHighScore(
            file_name, chighscores)
        if is_writing_error:
            raise Exception("incorrect write highscore")

    def __drive_handle(self, init_data: Dict[str, Any] = None) -> None:
        """Manages the driving state

        Parameters
        ----------
        init_data : Dict[str, Any], optional
            Initialization dictionary for tests, by default None
        """

        self.__road.shift_downward()
        self.__field.shift_downward()
        self.__npc_handle(init_data)
        self.__check_collision()
        self.__check_overtake()

    def __check_collision(self) -> None:
        """Checks for collisions between player and NPC cars"""
        if len(self.__npcs):
            first_npc: Car = self.__npcs[0]
            if any(x == y for x in self.__car.body for y in first_npc.body):
                self.state = RaceStates.COLLISION

    def __check_overtake(self) -> None:
        """Checks if the player is overtaking a NPC car"""
        if len(self.__npcs):
            if self.__npcs[0].top.y == -1:
                self.state = RaceStates.OVERTAKE

    def __shift_handle(self) -> None:
        """Hanlde change lanes, colision evaluation"""
        key: Optional[dirs] = self.__key
        if key:
            y: int = Car.cls_height() - 1
            if key == dirs.LEFT:
                x: int = Car.cls_width()
            elif key == dirs.RIGHT:
                x = self.__field.width - Car.cls_width() - 1

            if self.__npcs:
                self.__check_overlay(x)
            if self.state != RaceStates.COLLISION:
                self.__car.move(Point(x=x, y=y))
            self.__check_collision()
            self.__key = None
        else:
            self.state = RaceStates.DRIVE
            self.__drive_handle()

    def __check_overlay(self, new_x: int):
        """Checks collision when change lanes

        Parameters
        ----------
        new_x : int
            Potential abscissa of the new side of the field
        """

        car_points: List[Point] = self.car.body
        npc_points: List[Point] = self.__npcs[0].body
        top_car: Point = car_points[0]
        top_npc: Point = npc_points[0]
        if top_car.x == top_npc.x:
            if top_car.y in [p.y for p in npc_points]:
                self.state = RaceStates.COLLISION
        elif new_x == top_npc.x:
            if top_npc.y in [p.y for p in car_points]:
                self.state = RaceStates.COLLISION

    def __collision_handle(self):
        """Set end state and write highscore"""
        self.state = RaceStates.GAME_OVER
        if self.score > self.__highscore:
            self.__highscore = self.score

    def __overtake_handle(self):
        """Score increment, level up evaluation, and removes first nps"""
        self.state = RaceStates.DRIVE
        self.__score += 1
        if self.__score % self.__overtake_increment == 0:
            if self.__speed < self.__speed_limit:
                self.__speed += 1
        if self.__npcs:
            self.__npcs.popleft()

    def __npc_handle(self, init_data: Dict[str, Any] = None) -> None:
        """Spawn NPC's car and moves all of them

        Parameters
        ----------
        init_data : Dict[str, Any], optional
            Initialization dictionary for tests, by default None
        """

        if self.__delay_to_npc == 0:
            y: int = self.__field.height + Car.cls_height() - 1
            init_side: Optional[str] = None
            if init_data and init_data.get("npc_side", None) is not None:
                init_side = init_data["npc_side"]
            self.__npcs.append(self.car_init(y, init_side))
            delay: int = 0
            if init_data and init_data.get("distance", None) is not None:
                delay = init_data["distance"]
            else:
                minimum_distance: int = 2 * Car.cls_height() + 1
                maximun_distance: int = minimum_distance * 2
                delay = r.randint(minimum_distance, maximun_distance)
            self.__delay_to_npc = delay

        self.__delay_to_npc -= 1
        for npc in self.__npcs:
            npc.downward()

    def __place_npcs(self) -> None:
        """Place NPC on field"""
        for npc in self.__npcs:
            self.__field.place_car(npc)

    def set_highscore(self, value: int):
        """Set highscore

        Parameters
        ----------
        value : int
            given value
        """
        self.__highscore = value

    def show(self) -> None:
        """Print field of game"""

        return self.__field.show()
