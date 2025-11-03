"""Linear algebra package - hierarchy implemented in C++."""
from __future__ import annotations

import sys

# Re-export the C++ module structure
from ..._core.math.linalg import vector

# Register as submodule so it can be imported directly
sys.modules['physics_1.math.linalg.vector'] = vector

__all__ = ["vector"]
