from __future__ import annotations

import sys as _sys
import types as _types

from ._core import __doc__, __version__
from ._core import example, math

__all__ = ["__doc__", "__version__", "example", "math"]


def _register_submodules(parent_name: str, module: _types.ModuleType) -> None:
    """Recursively register pybind11 submodules to enable nested imports."""
    _sys.modules[parent_name] = module
    for attr_name in dir(module):
        attr = getattr(module, attr_name)
        if isinstance(attr, _types.ModuleType) and not attr_name.startswith("_"):
            _register_submodules(f"{parent_name}.{attr_name}", attr)


# Register all pybind11 submodules automatically
_register_submodules(f"{__name__}.example", example)
_register_submodules(f"{__name__}.math", math)

# Clean up namespace
del _sys, _types, _register_submodules
