#!/usr/bin/env python3
"""The module is a grpc server sending stream of spaceship entries

The server provide a response-streaming endpoint where it receives
a set of coordinates in the equatorial system and responds with
a stream of spaceship entries.
The main protocol used for communication - gRPC

The script requires modules created based on the proto file, the grpc
module for creating a server based on the protocol, random - for
generating spaceship parameters, the futures module for concurrent
access to the server, os module - to get environment variable,
sys - to add modules from others catalogs
"""

import grpc
import random as r
from typing import List, Dict, Any, Generator
from concurrent import futures
import os
import sys
sys.path.append("../protobuf/")
sys.path.append("../common_files")
from battleship_pb2 import battleship  # type: ignore # noqa: E402
import battleship_pb2_grpc as pb2g  # type: ignore # noqa: E402
from common import get_json, prompt_env_var  # type: ignore # noqa: E402


class ExploreSpaceServicer(pb2g.ExploreSpaceServicer):
    """Class-service for generate messages

    Service running on the server that generates a stream of
    messages representing the protobuf battleship class.

    Attributes
    ----------
    __files : Dict[str, Any]
        Files required to generate spacehip parameters

    Methods
    -------
    get_battleships(self, request, context) -> Generator[battleship]
        Generates battleships based on the provided coordinates
    __get_ship_name(self, align) -> str
        Generates a random battleship name
    __get_ship_length(self, class_name) -> float
        Generates a random battleship length
    __get_ship_crew_size(self, class_name) -> int
        Generates a random battleship crew size
    __write_ship_officers(self, bship) -> None
        Generates a random number of officer class messages
    """

    def __init__(self, files) -> None:
        """Files initialization

        Parameters
        ----------
        files : Dict[str, Any]
            Files required to generate spacehip parameters
        """

        self.__files: Dict[str, Any] = files

    def get_battleships(self, request, context) -> Generator[battleship,
                                                             None, None]:
        """Generates battleships based on the provided coordinates

        Parameters
        ----------
        request : coordinates_request
            A message containing coordinates
        context : grpc.ServicerContext
            The RPC context

        Yields
        ------
        Generator[battleship, None, None]
            Issues a generated message of the battleship class
        """

        seed_value: int = request.coordinates
        r.seed(seed_value)
        ships: int = r.randint(1, 10)
        ship_classes: int = len(battleship.ship_classes.keys())
        while ships:
            bship: battleship = battleship()
            bship.alignment = r.randint(0, 1)
            bship.name = self.__get_ship_name(bship.alignment)
            bship.ship_class = r.randint(0,  ship_classes - 1)
            class_name: str = bship.ship_classes.Name(bship.ship_class)
            bship.length = self.__get_ship_length(class_name)
            bship.crew_size = self.__get_ship_crew_size(class_name)
            bship.armed = True if r.randint(1, 2) % 2 == 0 else False
            self.__write_ship_officers(bship)
            ships -= 1
            yield bship

    def __get_ship_name(self, align: int) -> str:
        """Generates a random battleship name

        Parameters
        ----------
        align : int
            The value represents the alignment of the battleship

        Returns
        -------
        str
            The name of battleship
        """

        if align == battleship.alignments.Enemy:
            name: str = r.choice(self.__files['ship_names'] + ['Unknown'])
        else:
            name = r.choice(self.__files['ship_names'])
        return name

    def __get_ship_length(self, class_name: str) -> float:
        """Generates a random battleship length

        Parameters
        ----------
        class_name : str
            The class of the battleship

        Returns
        -------
        str
            The length of battleship
        """

        lengths: str = self.__files['constraints'][class_name]['length']
        lower, higher = [int(i) for i in lengths.split('-')]
        coef: float = 0.15
        length: float = r.uniform(lower * (1 - coef), higher * (1 + coef))
        return length

    def __get_ship_crew_size(self, class_name: str) -> int:
        """Generates a random battleship crew size

        Parameters
        ----------
        class_name : str
            The class of the battleship

        Returns
        -------
        str
            The crew size of battleship
        """

        sizes: str = self.__files['constraints'][class_name]['crew_size']
        lower, higher = [int(i) for i in sizes.split('-')]
        coef: float = 0.15
        size: int = int(r.uniform(lower * (1 - coef), higher * (1 + coef)))
        return size

    def __write_ship_officers(self, bship: battleship) -> None:
        """Generates a random number of officer class messages

        Parameters
        ----------
        bship : battleship
            The battleship message class
        """

        if bship.alignment == battleship.alignments.Ally:
            officers_min: int = 1
        else:
            officers_min = 0
        officers_max: int = 10
        officers: int = r.randint(officers_min, officers_max)
        while officers:
            officer: battleship.officer = battleship.officer()
            officer.first_name = r.choice(
                self.__files['officer_names']).split()[0]
            officer.last_name = r.choice(
                self.__files['officer_names']).split()[-1]
            officer.rank = r.choice(self.__files['rank_names'])
            bship.officers.append(officer)
            officers -= 1


def get_list(file: str) -> List[str]:
    """Get the list from text file

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
    List[str]
        List obtained by parsing file strings
    """

    lst: List[str] = []
    with open(file, 'r') as inp:
        lst = [i.rstrip('\n') for i in inp.readlines()]
    if not len(file):
        raise IOError(file)
    return lst


def data_initialization() -> Dict[str, Any]:
    """Initialization the data that generates messages

    Raises
    ------
    AttributeError
        if DATA_DIR environment variable (the path to files necessary
        to generate spacehip parameters) is not set

    Returns
    -------
    Dict[str, Any]
        A dictionary obtained as a result of parsing files, where keys
        are file names, the values ​​are a list or dictionary of strings
        for generating ship parameters.
    """

    data: str | None = os.getenv("DATA_DIR")
    if data is None:
        clue: str = "The DATA_DIR environment variable is not set"
        raise AttributeError(clue)
    ship_names_filename: str = 'ship_names'
    officer_names_filename: str = 'officer_names'
    rank_names_filename: str = 'rank_names'
    constrs_filename: str = 'constraints'

    ship_names: List[str] = get_list(f'{data}/{ship_names_filename}.txt')
    officer_names: List[str] = get_list(f'{data}/{officer_names_filename}.txt')
    rank_names: List[str] = get_list(f'{data}/{rank_names_filename}.txt')
    constraints: Dict[str, str] = get_json(f'{data}/{constrs_filename}.json')

    files_map: Dict[str, Any] = {ship_names_filename: ship_names,
                                 officer_names_filename: officer_names,
                                 rank_names_filename: rank_names,
                                 constrs_filename: constraints}
    return files_map


def serve() -> None:
    """Start the server"""
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    files_map = data_initialization()
    pb2g.add_ExploreSpaceServicer_to_server(
        ExploreSpaceServicer(files_map), server)
    server.add_insecure_port('localhost:8888')
    server.start()
    print('Server started...')
    server.wait_for_termination()


def main() -> None:
    """The server start and errors handle"""
    try:
        serve()
    except ValueError as e:
        print(f'Error: {e}')
    except IOError as e:
        print(f'File not found: {e}')
    except AttributeError as e:
        print(f'{e}')
        env_var: str = 'DATA_DIR'
        is_restart: bool = prompt_env_var(env_var)
        main() if is_restart else None


if __name__ == '__main__':
    main()
