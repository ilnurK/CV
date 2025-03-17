"""The module implements CRUD operations with the database

The script requires psycopg2 and sqlalchemy to work directly with
Postgresql database, data_tables - stores the ORM table models,
json - needs to output data in JSON format
"""

from sqlalchemy import text
from sqlalchemy.orm import Query, Session
from sqlalchemy.dialects.postgresql import insert
import psycopg2
import data_tables as dt
import json
from typing import List, Dict, Optional


def create_db_and_user(args: Dict[str, str]) -> None:
    """Create database and user

    Checking the database connection, if the database
    or user doesn't exist, creates it

    Parameters
    ----------
    args: Dict[str, str]
        A dictionary containing the arguments needed to connect to the database
    """

    conn = psycopg2.connect(host=args['host'], database=args['std'],
                            user=args['std'], password=args['std'])
    conn.autocommit = True

    def user_exists(cursor: conn.cursor) -> bool:
        """Checking the existence of a database user

        Parameters
        ----------
        cursor: conn.cursor
            A special object that makes requests and receives their results
        """

        command: str = "SELECT 1 FROM pg_catalog.pg_user WHERE usename"
        cursor.execute(f"{command} = '{args['user']}'")
        return cursor.fetchone() is not None

    def database_exists(cursor) -> bool:
        """Checking the existence of a database

        Parameters
        ----------
        cursor: conn.cursor
            A special object that makes requests and receives their results
        """

        command: str = "SELECT 1 FROM pg_catalog.pg_database WHERE datname"
        cursor.execute(f"{command} = '{args['base']}'")
        return cursor.fetchone() is not None

    with conn.cursor() as cursor:
        if not user_exists(cursor):
            cmd = f"CREATE USER {args['user']} WITH PASSWORD '{args['pass']}'"
            cursor.execute(cmd)
        if not database_exists(cursor):
            cmd = f"CREATE DATABASE {args['base']} OWNER {args['user']}"
            cursor.execute(cmd)

    conn.close()


def ship_register(ship, session: Session, is_scan: bool) -> None:
    """Adding records from battleship messages to tables

    Parameters
    ----------
    session: Session
        The sqlalchemy session
    is_scan: bool
        Сlient's argument is it a scan or not
    """

    ship['ship_class'] = ship.pop('class')
    officers_lst: List[Dict[str, str]] = ship.pop('officers')
    for ofc in officers_lst:
        officer_insert: insert = insert(dt.Officer).values(**ofc)
        query: Query = officer_insert.on_conflict_do_nothing(
            index_elements=["first_name", "last_name", "rank"]
        )

        session.execute(query)
        officer: Optional[dt.Officer] =\
            session.query(dt.Officer).filter_by(**ofc).first()
        officer_id: Optional[int] = officer.officer_id if officer else None

        battleship_insert: insert = insert(dt.Battleship).values(
                **ship, officer_id=officer_id)
        query = battleship_insert.on_conflict_do_nothing(
            index_elements=['name', 'officer_id'])
        session.execute(query)
        if is_scan and officer_id:
            traitor_scan(officer_id, session)

    session.commit()


def traitor_scan(officer_id: int, session: Session) -> None:
    """Checking for traitors and adding them in data_traitors table

    Parameters
    ----------
    officer_id: int
        The traitorous officer id
    session: Session
        The sqlalchemy session
    """

    officer_ships: Query[dt.Battleship] = session.query(dt.Battleship).\
        filter_by(officer_id=officer_id)
    is_traitor: bool = False
    officer_example: Optional[dt.Battleship] = officer_ships.first()
    if officer_example:
        example_alignment: str = officer_example.alignment
        for ship in officer_ships:
            if ship.alignment != example_alignment:
                is_traitor = True
                break
    if is_traitor:
        officer: dt.Officer | None = session.query(dt.Officer).\
            filter_by(officer_id=officer_id).first()
        if officer:
            traitor: insert = insert(dt.Traitor).\
                values(officer_id=officer.officer_id)
            query: Query = traitor.\
                on_conflict_do_nothing(index_elements=['officer_id'])
            session.execute(query)

    session.commit()


def traitors_handle(session: Session) -> None:
    """Output traitors from table in json format

    Parameters
    ----------
    session: Session
        The sqlalchemy session
    """

    traitors: List[dt.Traitor] = session.query(dt.Traitor).all()
    for traitor in traitors:
        officer: Optional[dt.Officer] = session.query(dt.Officer).filter_by(
            officer_id=traitor.officer_id).first()
        if officer:
            res: Dict[str, str] = {'first_name': officer.first_name,
                                   'last_name': officer.last_name,
                                   'rank': officer.rank}
            print(json.dumps(res))


def traitors_clear(session: Session) -> None:
    """Drop values from data_traitor table

    Parameters
    ----------
    session: Session
        The sqlalchemy session
    """

    session.query(dt.Traitor).delete()
    session.commit()


def tables_clear(session: Session) -> None:
    """Drop all tables

    Parameters
    ----------
    session: Session
        The sqlalchemy session
    """

    session.query(dt.Officer).delete()
    session.query(dt.Battleship).delete()
    session.query(dt.Traitor).delete()
    session.commit()

    metadata = dt.Base.metadata

    for table in metadata.sorted_tables:
        for column in table.columns:
            if column.autoincrement is True:
                key: str = table.name + '_' + column.name + '_seq'
                session.execute(text(f"ALTER SEQUENCE {key} RESTART WITH 1;"))
    session.commit()
