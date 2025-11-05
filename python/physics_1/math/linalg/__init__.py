from __future__ import annotations

from .._math import linalg as _linalg

# Dynamically re-export all public symbols from _linalg
__all__ = ["__doc__", "__version__"]
for _name in dir(_linalg):
    if not _name.startswith("_"):
        globals()[_name] = getattr(_linalg, _name)
        __all__.append(_name)
del _name  # Clean up the loop variable
