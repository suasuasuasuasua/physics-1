"""Physics 1 Module - All functionality implemented in C++ via pybind11.

The package hierarchy is created entirely in C++ using pybind11's def_submodule().
This file simply imports from the _core C++ extension and registers modules for Python's import system.
"""
from __future__ import annotations
import sys

# Import the C++-defined package hierarchy from _core
# The C++ code creates: _core.example.functions, _core.math.constants, _core.math.linalg.vector
from _core import __doc__, __version__, example, math

# Register C++ submodules in sys.modules so Python's import system can find them
# This enables: from physics_1.example import functions, from physics_1.math.linalg import vector, etc.
sys.modules['physics_1.example'] = example
sys.modules['physics_1.example.functions'] = example.functions
sys.modules['physics_1.math'] = math
sys.modules['physics_1.math.constants'] = math.constants
sys.modules['physics_1.math.linalg'] = math.linalg
sys.modules['physics_1.math.linalg.vector'] = math.linalg.vector

__all__ = ["__doc__", "__version__", "example", "math"]
