from sqlalchemy import (
    Integer,
    String,
    Float,
    Boolean,
    ForeignKey,
    UniqueConstraint
)
from sqlalchemy.orm import DeclarativeBase, mapped_column  # type: ignore
from sqlalchemy.orm import Mapped, relationship
from typing import List, Optional, Tuple


class Base(DeclarativeBase):
    """Base class for ORM models"""
    pass


class Officer(Base):
    """data_officer table stores data from battleship's officer message

    The table stores values obtained from battleship messages in
    the officers field

    Attributes
    ----------
    __tablename__: str
        The table name
    officer_id: int
        The officers's id
    first_name: str
        The officers's first name
    last_name: str
        The officers's last name
    rank: str
        The officers's rank
    ship: Battleship
        The reference to table object data_ship
    traitor:
        The reference to table object data_traitor
    __table_args__: Tuple[UniqueConstraint]
        Constraints of table
    """

    __tablename__: str = 'data_officer'

    officer_id: Mapped[int] = mapped_column(
        Integer, primary_key=True, autoincrement=True)
    first_name: Mapped[str] = mapped_column(String)
    last_name: Mapped[str] = mapped_column(String)
    rank: Mapped[str] = mapped_column(String)

    ship: Mapped[List['Battleship']] = relationship(
        back_populates='officer',
        cascade="all, delete",
        passive_deletes=True)  # type: ignore
    traitor: Mapped['Traitor'] = relationship(
        argument='Traitor',
        back_populates='officer',
        cascade="all, delete",
        passive_deletes=True)  # type: ignore

    __table_args__: Tuple[UniqueConstraint] = (
        UniqueConstraint('first_name', 'last_name', 'rank'),)


class Battleship(Base):
    """data_ship table stores data from battleship message

    Attributes
    ----------
    id: str
        The battleship's id
    alignment: str
        The battleship's alignment
    name: str
        The battleship's name
    ship_class: str
        The battleship's class
    length: float
        The battleship's length
    crew_size: int
        The battleship's size of crew
    armed: bool
        The battleship's armed status
    officer_id: int | None
        The officer's id
    speed: int
        The battleship's speed
    officer
        The reference to table object data_traitor
    __table_args__: Tuple[UniqueConstraint]
        Constraints of table
    """

    __tablename__: str = 'data_ship'
    id: Mapped[str] = mapped_column(
        Integer,
        primary_key=True,
        autoincrement=True)
    alignment: Mapped[str] = mapped_column(String)
    name: Mapped[str] = mapped_column(String)
    ship_class: Mapped[str] = mapped_column(String, name='class')
    length: Mapped[float] = mapped_column(Float)
    crew_size: Mapped[int] = mapped_column(Integer)
    armed: Mapped[bool] = mapped_column(Boolean)
    officer_id: Mapped[Optional[int]] = mapped_column(
        Integer,
        ForeignKey('data_officer.officer_id', ondelete='CASCADE'),
        nullable=True)
    speed: Mapped[int] = mapped_column(Integer, nullable=True)

    officer: Mapped['Officer'] = relationship(
        back_populates='ship')  # type: ignore

    __table_args__: Tuple[UniqueConstraint] = (
        UniqueConstraint('name', 'officer_id'),)


class Traitor(Base):
    """data_traitor table stores traitorous officers

    The traitor table stores traitors - officers who are on both
    an allied and enemy ship, added by scan ships on given coordinates

    Attributes
    ----------
    __tablename__: str
        The table name
    traitor_id: int
        The traitor's id
    officer_id: int
        The officer's id
    officer:
        The reference to table object data_officer
    __table_args__: Tuple[UniqueConstraint]
        Constraints of table
    """

    __tablename__: str = 'data_traitor'

    traitor_id: Mapped[int] = mapped_column(
        Integer, primary_key=True, autoincrement=True)
    officer_id: Mapped[int] = mapped_column(
        Integer, ForeignKey('data_officer.officer_id', ondelete='CASCADE'))

    officer: Mapped['Officer'] = relationship(
        argument='Officer', back_populates='traitor')  # type: ignore

    __table_args__: Tuple[UniqueConstraint] = (UniqueConstraint('officer_id'),)
