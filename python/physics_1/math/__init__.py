"""Math package - hierarchy implemented in C++."""
from __future__ import annotations

import sys

# Re-export constants from C++ module
from .._core.math import constants

# linalg is a Python package (don't import from _core here)
from . import linalg

# Register constants as a submodule so it can be imported directly
sys.modules['physics_1.math.constants'] = constants

__all__ = ["constants", "linalg"]
