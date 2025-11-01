"""
Some example functions demoing pybind11
"""
from __future__ import annotations
import typing
__all__: list[str] = ['add', 'mul', 'sub']
def add(i: typing.SupportsInt, j: typing.SupportsInt) -> int:
    """
            Add two numbers
    """
def mul(i: typing.SupportsInt, j: typing.SupportsInt) -> int:
    ...
def sub(i: typing.SupportsInt, j: typing.SupportsInt) -> int:
    """
            Subtract two numbers
    """
