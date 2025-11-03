"""Vector module with Vector2 class for 2D vector operations."""
from __future__ import annotations

def _get_linalg_core():
    """Lazy import of _core.linalg to avoid circular imports."""
    try:
        # Try importing from _core first (when _core is standalone)
        from _core import linalg
        return linalg
    except ImportError:
        pass
    
    # Try importing from physics_1._core
    try:
        from physics_1._core import linalg
        return linalg
    except ImportError:
        pass
    
    # If all else fails, try relative import
    from ..._core import linalg
    return linalg

_linalg_core = _get_linalg_core()

# Re-export Vector2 from the C++ module
Vector2 = _linalg_core.Vector2

__all__ = ["Vector2"]
