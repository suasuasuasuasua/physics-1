"""
Pybind11 example plugin
-----------------------

.. currentmodule:: physics_1

.. autosummary::
    :toctree: _generate

    add
    subtract
"""

def add(i: int, j: int) -> int:
    """
    Add two numbers
    """

def sub(i: int, j: int) -> int:
    """
    Subtract two numbers
    """

def reduce(nums: list[float], initial: float = 0) -> int:
    """
    Reduce a list
    """
