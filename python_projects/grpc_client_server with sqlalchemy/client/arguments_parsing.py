"""Argument parsing module for client to receive battleship messages

The script requires argparse module to check inputted coordinates
and arguments, dataclasses for creating a typechecked class
"""
import argparse
from dataclasses import dataclass
from typing import List, Any


@dataclass
class Args():
    """Class for storing parsed values

    Attributes
    ----------
    ra_hour: int
        Right ascension's hours
    ra_min: int
        Right ascension's minutes
    ra_sec: float
        Right ascension's seconds
    dec_deg: int
        Declension's degrees
    dec_min: int
        Declension's minutes
    dec_sec: float
        Declension's seconds
    scan: bool
        Is scan mode
    list_traitors: bool
        Is traitors print mode
    list_clear: bool
        Is traitors clean mode
    tables_clear: bool
        Is delete tables mode
    """

    ra_hour: int
    ra_min: int
    ra_sec: float
    dec_deg: int
    dec_min: int
    dec_sec: float
    scan: bool
    list_traitors: bool
    list_clear: bool
    tables_clear: bool


def args_parse() -> Args:
    """CLI arguments parsing

    Raises
    ------
    ValueError
        If args are incompatible
    """

    clue: str = "Write the galactic coordinates in equatorial system of \
desired point. Use 'scan' keyword to searching for 'traitors' - the same \
officers could be found on both allied and enemy ships. 'list_traitors' print \
a list of JSON with 'traitors' names. 'list_clear' clear traitors table"
    prs = argparse.ArgumentParser(usage=clue, description=clue)
    clue = '"scan", "list_traitors", "list_clear" or coordinates'
    prs.add_argument('input', nargs='+', help=clue)
    inp: List[str] = prs.parse_args().input
    coords: List[str] = ['ra_hour', 'ra_min',
                         'ra_sec', 'dec_deg', 'dec_min', 'dec_sec']
    actions: List[str] = ['scan', 'list_traitors',
                          'list_clear', 'tables_clear']
    def_values: List[Any] = [0] * len(coords) + [False] * len(actions)
    args = Args(**dict(zip(coords + actions, def_values)))
    first_arg = inp[0]
    if first_arg in actions[1:]:
        if len(inp) > 1:
            raise ValueError("list argument doesn't need other arguments")
        if first_arg == 'list_traitors':
            args.list_traitors = True
        elif first_arg == 'tables_clear':
            args.tables_clear = True
        else:
            args.list_clear = True
    elif first_arg == 'scan' or first_arg.isdigit():
        coords_init(inp, args)
    else:
        raise ValueError(f'equatorial system uses 6 coordinates or {actions} '
                         'arguments')
    return args


def coords_init(inp: List[str], args: Args) -> None:
    """Check input coordinates

    Parameters
    ----------
    inp: List[str]
        List of entered values
    args: Args
        The entered values class

    Raises
    ------
    ValueError
        if coordinates doesn't fit required type
    """

    start_idx: int = 0
    if inp[0] == 'scan':
        start_idx = 1
        args.scan = True
    coord_num: int = 6 + start_idx
    if len(inp) != coord_num:
        raise ValueError('equatorial system uses 6 coordinates and optional'
                         'scan argument')

    values: List[str] = inp[start_idx:coord_num]
    try:
        args.ra_hour = int(values.pop(0))
        args.ra_min = int(values.pop(0))
        args.ra_sec = float(values.pop(0))

        args.dec_deg = int(values.pop(0))
        args.dec_min = int(values.pop(0))
        args.dec_sec = float(values.pop(0))
    except ValueError:
        raise ValueError('incorrect types of coordinates')

    is_incorrect: bool = False
    if args.ra_hour < 0 or args.ra_hour > 23:
        is_incorrect = True
    elif args.ra_min < 0 or args.ra_min >= 60:
        is_incorrect = True
    elif args.ra_sec < 0 or args.ra_sec >= 60:
        is_incorrect = True
    elif args.dec_deg < -90 or args.dec_deg > 90:
        is_incorrect = True
    elif args.dec_min < 0 or args.dec_min >= 60:
        is_incorrect = True
    elif args.dec_sec < 0 or args.dec_sec >= 60:
        is_incorrect = True

    if is_incorrect:
        raise ValueError("coordinates don't fit the equatorial system")
