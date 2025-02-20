"""The script tests FSM class"""
import pytest
from import_module import *  # noqa: F40*
from s21_race import FSM, RaceStates, dirs, Car, ctypes
from typing import Dict, Any, Tuple


@pytest.fixture
def init_fsm() -> FSM:
    return FSM()


def test_cycle(init_fsm: FSM) -> None:
    state: RaceStates = init_fsm.set_state(state=RaceStates.START)
    assert state == RaceStates.DRIVE


def test_move(init_fsm: FSM) -> None:
    state: RaceStates = init_fsm.set_state(state=RaceStates.START,
                                           key=dirs.LEFT)
    assert state == RaceStates.DRIVE


def test_move_unstable(init_fsm: FSM) -> None:
    init_fsm.set_state(state=RaceStates.START)
    state: RaceStates = init_fsm.unstable_state(key=dirs.LEFT)
    assert state == RaceStates.CHANGE_LANES
    state = init_fsm.unstable_state()
    assert state == RaceStates.DRIVE


def test_npc_init(init_fsm: FSM) -> None:
    init_dict: Dict[str, Any] = {
        "duration_to_npc": 0
    }
    init_fsm.set_state(state=RaceStates.START,
                       init_data=init_dict)
    n: int = 4
    for _ in range(n):
        init_fsm.set_state(state=RaceStates.DRIVE)
    assert len(init_fsm.npcs) == 1
    for i in range(n - 1):
        assert init_fsm.car.symbol in init_fsm.body[init_fsm.height - i - 1]


def test_road_down_when_turn(init_fsm: FSM) -> None:
    fsm = init_fsm
    border_fill, _ = fsm.field.border_pattern
    cr: int = 0

    fsm.set_state(state=RaceStates.START)
    if cr < border_fill:
        assert fsm.field.body[0][0] == fsm.field.border
    else:
        cr -= border_fill
        assert fsm.field.body[0][0] == fsm.field.road
    cr += 1

    fsm.set_state(state=RaceStates.DRIVE)
    if cr < border_fill:
        assert fsm.field.body[0][0] == fsm.field.border
    else:
        cr -= border_fill
        assert fsm.field.body[0][0] == fsm.field.road
    cr += 1

    fsm.set_state(state=RaceStates.DRIVE)
    if cr < border_fill:
        assert fsm.field.body[0][0] == fsm.field.border
    else:
        cr -= border_fill
        assert fsm.field.body[0][0] == fsm.field.road
    cr += 1
    """
    #        #
    #        #

    #        #
    #        #
    #        #

    #        #
    #        #
    #        #

    #        #
    #        #
    #        #

    #        #
    #  0     #
    # 000    #
       0
    # 0 0    #
    """

    state = fsm.set_state(state=RaceStates.DRIVE, key=dirs.LEFT)
    assert state == RaceStates.DRIVE
    if cr < border_fill:
        assert fsm.field.body[0][0] == fsm.field.border
    else:
        cr -= border_fill
        assert fsm.field.body[0][0] == fsm.field.road
    cr += 1
    """
    #    0 0 #
    #        #
    #        #

    #        #
    #        #
    #        #

    #        #
    #        #
    #        #

    #        #
    #        #
    #        #

    #  0     #
    # 000    #
    #  0     #
      0 0
    """


@pytest.fixture
def fsm_with_init_data() -> Tuple[FSM, Dict[str, Any]]:
    fsm = FSM()
    init_dict: Dict[str, Any] = {
        "hero_side": "left",
        "npc_side": "right",
        "duration_to_npc": 0,
        "distance": 2 * Car.cls_height() + 1
    }
    fsm.set_state(state=RaceStates.START, init_data=init_dict)
    for _ in range(fsm.field.height - Car.cls_height() - 1):
        fsm.set_state(state=RaceStates.DRIVE, init_data=init_dict)
    return fsm, init_dict


def test_overtake_unstable(
        fsm_with_init_data: Tuple[FSM, Dict[str, Any]]) -> None:
    fsm, init_data = fsm_with_init_data
    """
    #        #
    #        #
    #     0  #
         000
    #     0  #
    #    0 0 #
    #        #

    #        #
    #        #
    #        #
          0
    #    000 #
    #     0  #
    #    0 0 #
       0
    # 000    #
    #  0     #
    # 0 0    #
    """
    for _ in range(Car.cls_height() * 2):
        state = fsm.unstable_state()

    """
    #        #
    #     0  #
    #    000 #
          0
    #    0 0 #
    #        #
    #        #

    #        #
    #        #
    #     0  #
         000
    #     0  #
    #    0 0 #
    #        #

    #  0     #
    # 000    #
    #  0     #
      0 0 0
    """

    state = fsm.unstable_state(init_data=init_data)
    assert state == RaceStates.OVERTAKE
    fsm.unstable_state(init_data=init_data)
    assert fsm.score == 1


def test_overtake(fsm_with_init_data: Tuple[FSM, Dict[str, Any]]) -> None:
    fsm, init_data = fsm_with_init_data
    state = fsm.set_state(state=RaceStates.START, init_data=init_data)
    for _ in range(Car.cls_height() * 2):
        state = fsm.set_state(state=RaceStates.DRIVE, init_data=init_data)
    assert state == RaceStates.DRIVE
    fsm.set_state(state=RaceStates.DRIVE, init_data=init_data)
    assert fsm.score == 1


def test_overtakes_unstable(
        fsm_with_init_data: Tuple[FSM, Dict[str, Any]]) -> None:
    N: int = 5
    fsm, init_data = fsm_with_init_data
    overtake_counter: int = 0
    state = fsm.set_state(state=RaceStates.START, init_data=init_data)
    for _ in range((Car.cls_height() * 2 + 1) * N + N):
        state = fsm.unstable_state(init_data=init_data)
        if state == RaceStates.OVERTAKE:
            overtake_counter += 1
    assert overtake_counter == 5
    assert fsm.score == 5
    assert fsm.speed == 2


def test_overtakes(fsm_with_init_data: Tuple[FSM, Dict[str, Any]]) -> None:
    N: int = 5
    fsm, init_data = fsm_with_init_data
    fsm.set_state(state=RaceStates.START, init_data=init_data)
    for _ in range(Car.cls_height() * 2 * N + N):
        fsm.set_state(state=RaceStates.DRIVE, init_data=init_data)
    assert fsm.score == 5
    assert fsm.speed == 2


def test_move_and_collision_unstable(
    fsm_with_init_data: Tuple[FSM, Dict[str, Any]]
) -> None:
    fsm, init_data = fsm_with_init_data

    state = fsm.unstable_state(key=dirs.RIGHT, init_data=init_data)
    assert state == RaceStates.CHANGE_LANES

    state = fsm.unstable_state()
    assert state == RaceStates.DRIVE

    state = fsm.unstable_state()
    assert state == RaceStates.DRIVE
    """
    #        #
    #        #
    #     0  #
         000
    #     0  #
    #    0 0 #
    #        #

    #        #
    #        #
    #        #
          0
    #    000 #
    #     0  #
    #    000 #
         000
    #     0  #
    #    0 0 #
    """

    state = fsm.unstable_state()
    assert state == RaceStates.COLLISION
    """
    #        #
    #        #

    #        #
    #        #
    #     0  #
         000
    #     0  #
    #    0 0 #
    #        #

    #        #
    #        #
    #        #
          0
    #    000 #
    #     0  #
    #    000 #
          0
    #    0 0 #
    """


def test_move_and_collision(
    fsm_with_init_data: Tuple[FSM, Dict[str, Any]]
) -> None:
    fsm, init_data = fsm_with_init_data
    key = dirs.RIGHT
    fsm.set_state(state=RaceStates.START, key=key, init_data=init_data)
    fsm.set_state(state=RaceStates.DRIVE)
    fsm.set_state(state=RaceStates.DRIVE)
    state = fsm.set_state(state=RaceStates.DRIVE)
    assert state == RaceStates.GAME_OVER


def test_move_and_avoid_collision_unstable(
    fsm_with_init_data: Tuple[FSM, Dict[str, Any]]
) -> None:
    fsm, init_data = fsm_with_init_data

    state = fsm.unstable_state(key=dirs.RIGHT, init_data=init_data)
    assert state == RaceStates.CHANGE_LANES

    state = fsm.unstable_state()
    assert state == RaceStates.DRIVE

    state = fsm.unstable_state(key=dirs.LEFT)
    assert state == RaceStates.CHANGE_LANES

    state = fsm.unstable_state()
    assert state == RaceStates.DRIVE


def test_move_pause_and_avoid_collision(
    fsm_with_init_data: Tuple[FSM, Dict[str, Any]]
) -> None:
    fsm, _ = fsm_with_init_data
    key = dirs.RIGHT
    state = fsm.set_state(state=RaceStates.START, key=key)
    assert state == RaceStates.DRIVE
    key = dirs.LEFT
    state = fsm.set_state(state=RaceStates.DRIVE, key=key)
    assert state == RaceStates.DRIVE
    state = fsm.set_state(state=RaceStates.DRIVE)
    assert state == RaceStates.DRIVE


@pytest.fixture
def highscore_fixture(fsm_with_init_data: Tuple[FSM, Dict[str, Any]]) -> FSM:
    N: int = 5
    fsm, init_data = fsm_with_init_data
    fsm.set_state(state=RaceStates.START, init_data=init_data)
    for _ in range(Car.cls_height() * 2 * N + N):
        fsm.set_state(state=RaceStates.DRIVE, init_data=init_data)
    fsm.set_state(state=RaceStates.COLLISION, init_data=init_data)
    fsm.write_highscore()
    return fsm


@pytest.fixture
def hscore_path() -> str:
    fsm = FSM()
    fsm.lib_hscore.S21GetLogFilePath.argtypes = (
        ctypes.c_char_p, ctypes.POINTER(ctypes.c_bool))
    fsm.lib_hscore.S21GetLogFilePath.restype = ctypes.c_char_p

    fsm.lib_hscore.S21GetRaceLogFileName.restype = ctypes.c_char_p
    file_name = fsm.lib_hscore.S21GetRaceLogFileName()
    is_incorrect_path = ctypes.c_bool()
    path = fsm.lib_hscore.S21GetLogFilePath(file_name, is_incorrect_path)
    if is_incorrect_path:
        raise RuntimeError("incorrect path")
    return path


def test_highscore_record(highscore_fixture: FSM, hscore_path: str) -> None:
    with open(hscore_path, "r") as f:
        hscore = f.readline()
        assert int(hscore) == 5


def test_highscore_read(hscore_path: str) -> None:
    N: int = 123
    with open(hscore_path, "w") as f:
        f.writelines(str(N))
    fsm = FSM()
    assert fsm.read_highscore() == N
    with open(hscore_path, "w") as f:
        pass
    assert fsm.read_highscore() == 0
