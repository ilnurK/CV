"""The script tests Car class"""
import pytest
from copy import deepcopy
from import_module import *  # noqa: F40*
from s21_race import Car, Point
from typing import List


def test_left_init() -> None:
    """Tests left initialization of car"""
    point: Point = Point(3, 3)
    car: Car = Car(point)
    body: List[Point] = car.body
    assert body[0] == Point(x=3, y=3)
    assert body[1] == Point(x=3, y=2)
    assert body[2] == Point(x=2, y=2)
    assert body[3] == Point(x=4, y=2)
    assert body[4] == Point(x=3, y=1)
    assert body[5] == Point(x=2, y=0)
    assert body[6] == Point(x=4, y=0)


def test_right_init() -> None:
    """Tests right initialization of car"""
    point: Point = Point(x=6, y=3)
    car: Car = Car(point)
    body: List[Point] = car.body
    assert body[0] == Point(x=6, y=3)
    assert body[1] == Point(x=6, y=2)
    assert body[2] == Point(x=5, y=2)
    assert body[3] == Point(x=7, y=2)
    assert body[4] == Point(x=6, y=1)
    assert body[5] == Point(x=5, y=0)
    assert body[6] == Point(x=7, y=0)


@pytest.fixture
def init_car() -> Car:
    """Initialitates car

    Returns
    -------
    Car
        Initiated car
    """

    point: Point = Point(5, 10)
    car: Car = Car(point)
    return car


def test_move_car(init_car: Car) -> None:
    """Tests car's move

    Parameters
    ----------
    init_car : Car
        Initiated car
    """

    init_car.move(Point(x=4, y=7))
    body: List[Point] = init_car.body
    assert body[0] == Point(x=4, y=7)
    assert body[1] == Point(x=4, y=6)
    assert body[2] == Point(x=3, y=6)
    assert body[3] == Point(x=5, y=6)
    assert body[4] == Point(x=4, y=5)
    assert body[5] == Point(x=3, y=4)
    assert body[6] == Point(x=5, y=4)


def test_downward_car(init_car: Car) -> None:
    """Tests downward's car

    Parameters
    ----------
    init_car : Car
        Initiated car
    """
    init_body: List[Point] = deepcopy(init_car.body)
    init_car.downward()
    body: List[Point] = init_car.body
    shift: int = 1
    for i in range(len(body)):
        assert body[i].x == init_body[i].x
        assert body[i].y == init_body[i].y - shift


def test_downward_twice_car(init_car: Car) -> None:
    """Tests downward's car

    Parameters
    ----------
    init_car : Car
        Initiated car
    """

    init_body: List[Point] = deepcopy(init_car.body)
    init_car.downward()
    init_car.downward()
    body: List[Point] = init_car.body
    shift: int = 2
    for i in range(len(body)):
        assert body[i].x == init_body[i].x
        assert body[i].y == init_body[i].y - shift


def test_cars_getters(init_car: Car) -> None:
    """Tests car parameter getters

    Parameters
    ----------
    init_car : Car
        Initiated car
    """

    assert init_car.cls_height() == 4
    assert init_car.cls_width() == 3
    assert init_car.symbol == '0'
