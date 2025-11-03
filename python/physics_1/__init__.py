from __future__ import annotations

# Import the C++-defined package hierarchy
from ._core import example, math

try:
    from ._core import __doc__ as _doc
    from ._core import __version__ as _version
    __doc__ = _doc
    __version__ = _version
except (ImportError, AttributeError):
    __doc__ = "Physics 1 Module"
    __version__ = "dev"

__all__ = ["__doc__", "__version__", "example", "math"]
