from __future__ import annotations

import sys

from ._core import __doc__, __version__
from ._core import example, math

# pybind11's def_submodule automatically registers submodules in sys.modules,
# but under the _core namespace. We alias them to the physics_1 namespace for cleaner imports.
sys.modules[f"{__name__}.example"] = example
sys.modules[f"{__name__}.example.functions"] = example.functions
sys.modules[f"{__name__}.math"] = math
sys.modules[f"{__name__}.math.linalg"] = math.linalg

__all__ = ["__doc__", "__version__", "example", "math"]
