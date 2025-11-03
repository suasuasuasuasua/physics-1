"""Example package - hierarchy implemented in C++."""
from __future__ import annotations

import sys

# Re-export the C++ module structure
from .._core.example import functions

# Register as submodule so it can be imported directly
sys.modules['physics_1.example.functions'] = functions

__all__ = ["functions"]
