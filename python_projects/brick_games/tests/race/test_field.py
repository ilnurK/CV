"""The script tests Field class"""
import pytest
from import_module import *  # noqa: F40*
from s21_race import Field, Car, Point
from typing import List, Tuple


@pytest.fixture
def init_field() -> Field:
    """Initialitates field

    Returns
    -------
    Field
        Initiated field
    """
    return Field()


def test_field_init(init_field: Field) -> None:
    """Tests field initialization

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    lborders, rborders = check_free_road_and_get_borders(init_field)
    check_lists_identical(lborders, rborders)
    check_borders(init_field, lborders, rborders)


def check_free_road_and_get_borders(fd: Field) -> Tuple[List[str], List[str]]:
    """Checks the array between the boundaries for equality fd.road

    Parameters
    ----------
    fd : Field
        Initiated field

    Returns
    -------
    Tuple[List[str], List[str]]
        The boundaries lists
    """

    lborders: List[str] = []
    rborders: List[str] = []
    body: List[List[str]] = fd.body
    for y in range(fd.height):
        for x in range(fd.width):
            if x == 0:
                lborders.append(body[y][x])
            elif x == fd.width - 1:
                rborders.append(body[y][x])
            else:
                assert body[y][x] == fd.road
    return lborders, rborders


def check_lists_identical(a: List[str], b: List[str]) -> None:
    """Checks 2 lists for identity

    Parameters
    ----------
    a : List[str]
        The first list
    b : List[str]
        The second list
    """

    assert len(a) == len(b)
    for i in range(len(a)):
        assert a[i] == b[i]


def check_borders(fd: Field, lborders: List[str],
                  rborders: List[str], shift=0) -> None:
    """Check borders of field

    Parameters
    ----------
    fd : Field
        Initiated field
    lborders : List[str]
        The left border elements of field
    rborders : List[str]
        The right border elements of field
    shift : int, optional
        Shifts down by number, by default 0
    """

    fill_norm, free_norm = fd.border_pattern
    i = 0
    cr_fill: int = shift
    cr_free: int = 0
    while i < len(lborders):
        if cr_fill < fill_norm:
            assert lborders[i] == fd.border
            assert rborders[i] == fd.border
            cr_fill += 1
        else:
            if cr_free < free_norm:
                assert lborders[i] == fd.road
                assert rborders[i] == fd.road
                cr_free += 1
            else:
                cr_fill = 0
                cr_free = 0
                i -= 1
        i += 1


def test_field_downward(init_field: Field) -> None:
    """Tests downward method of field

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    init_field.shift_downward()
    lborders, rborders = check_free_road_and_get_borders(init_field)
    shift: int = 1
    check_borders(init_field, lborders, rborders, shift)


def test_field_downward_again(init_field: Field) -> None:
    """Tests downward method of field

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    init_field.shift_downward()
    init_field.shift_downward()
    lborders, rborders = check_free_road_and_get_borders(init_field)
    shift: int = 2
    check_borders(init_field, lborders, rborders, shift)


def test_field_place_car(init_field: Field) -> None:
    """Tests place npc car on field

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    car: Car = Car(Point(x=Car.cls_width(), y=Car.cls_height()))
    init_field.place_car(car)
    body: List[List[str]] = init_field.body
    for p in car.body:
        assert body[p.y][p.x] == car.symbol


def test_field_place_car_hero(init_field: Field) -> None:
    """Tests place hero car on field

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    car: Car = Car(Point(x=Car.cls_width() - 3, y=Car.cls_height()))
    with pytest.raises(RuntimeError):
        init_field.place_car(car, is_hero_car=True)


def test_field_show(init_field: Field) -> None:
    """Just for coverage

    Parameters
    ----------
    init_field : Field
        Initiated field
    """

    init_field.show()
