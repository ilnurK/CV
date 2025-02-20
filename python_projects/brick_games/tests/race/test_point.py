"""The script tests Point class"""
import pytest
from import_module import *  # noqa: F40*
from s21_race import Point


@pytest.fixture
def init_point() -> Point:
    """Initialitates start point

    Returns
    -------
    Point
        Initiated start point
    """

    return Point(5, 5)


def test_points_init(init_point: Point) -> None:
    """Tests point initialization

    Parameters
    ----------
    init_point : Point
        Initiated start point
    """

    p1: Point = Point(other=init_point, other_shift="up")
    assert p1.y == 6 and p1.x == 5
    p2: Point = Point(other=init_point, other_shift="down")
    assert p2.y == 4 and p2.x == 5
    p3: Point = Point(other=init_point, other_shift="left")
    assert p3.y == 5 and p3.x == 4
    p4: Point = Point(other=init_point, other_shift="right")
    assert p4.y == 5 and p4.x == 6
    with pytest.raises(ValueError):
        p5: Point = Point(other=init_point, other_shift="none")
    with pytest.raises(ValueError):
        p5 = Point(other=5)  # noqa: F841
    assert init_point == Point(other=init_point)
