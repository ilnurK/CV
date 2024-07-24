"""Helper functions for both the client and the server

The module requires json library - for parsing a file with which random
parameters will be generated, os - for environment variable prompt
"""

import json
import os
from typing import Dict


def get_json(file: str) -> Dict[str, str]:
    """Get the dictionary from JSON file

    Parameters
    ----------
    file : str
        The path to file

    Raises
    ------
    IOError
        If the file is not found or is empty

    Returns
    -------
    Dict[str, str]
        Dictionary obtained by parsing file strings
    """

    out: Dict[str, str] | None = None
    with open(file, 'r') as inp:
        out = json.load(inp)
    if out is None:
        raise IOError(file)
    return out


def prompt_env_var(var: str) -> bool:
    """Prompt to enter an environment variable

    Parameters
    ----------
    var : str
        Environment variable prompted for writing

    Returns
    -------
    bool
        Need to restart script or not
    """

    is_restart = False
    clue: str = f"Enter [y, n] to write {var} environment variable"
    "now or finish program"
    print(clue)
    inp: str = input().lower()
    if inp == 'y':
        is_restart = True
        clue = f"Write down the {var} variable - the path to files"
        "necessary to generate spacehip parameters"
        print(clue)
        os.environ[var] = input()
    elif inp == "n":
        clue = "Ok, script shutdown..."
        print(clue)
    else:
        is_correct = False
        while not is_correct:
            print("Please, enter only 'y' or 'n'")
            inp = input()
            if inp == 'y' or inp == 'n':
                is_correct = True
                is_restart = True if inp == 'y' else False
    return is_restart
