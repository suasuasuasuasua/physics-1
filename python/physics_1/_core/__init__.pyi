"""

        Physics 1 Module
        -----------------------

        .. currentmodule:: physics_1

        .. autosummary::
           :toctree: _generate
    
"""
from __future__ import annotations
from . import example
from . import linalg

__all__: list[str] = ['example', 'linalg', '__version__', '__doc__']
__version__: str
__doc__: str
