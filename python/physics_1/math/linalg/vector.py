"""Vector module with Vector2 class for 2D vector operations."""
from __future__ import annotations

def _get_linalg_core():
    """Lazy import of _core.linalg to avoid circular imports."""
    import sys
    if '_core' in sys.modules:
        from _core import linalg
        return linalg
    # Import physics_1._core if _core is not available
    from physics_1._core import linalg
    return linalg

_linalg_core = _get_linalg_core()

# Re-export Vector2 from the C++ module
Vector2 = _linalg_core.Vector2

__all__ = ["Vector2"]
