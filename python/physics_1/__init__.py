from __future__ import annotations

from . import example, math

# Import version and documentation from _core
try:
    from ._core import __doc__ as _core_doc
    from ._core import __version__ as _core_version
    __doc__ = _core_doc
    __version__ = _core_version
except ImportError:
    __doc__ = "Physics 1 Module"
    __version__ = "dev"

__all__ = ["__doc__", "__version__", "example", "math"]
