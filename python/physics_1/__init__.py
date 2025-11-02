from __future__ import annotations

import sys

from ._core import __doc__, __version__
from ._core import example, math

# Register submodules in sys.modules to enable direct imports
# This allows: from physics_1.example import functions
# This allows: from physics_1.math.linalg import Vector2
sys.modules["physics_1.example"] = example
sys.modules["physics_1.example.functions"] = example.functions
sys.modules["physics_1.math"] = math
sys.modules["physics_1.math.linalg"] = math.linalg

__all__ = ["__doc__", "__version__", "example", "math"]
