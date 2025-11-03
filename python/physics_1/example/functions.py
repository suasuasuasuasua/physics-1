"""Functions module with basic mathematical operations."""
from __future__ import annotations

def _get_example_core():
    """Lazy import of _core.example to avoid circular imports."""
    import sys
    if '_core' in sys.modules:
        from _core import example
        return example
    # Import physics_1._core if _core is not available
    from physics_1._core import example
    return example

_example_core = _get_example_core()

# Re-export functions from the C++ module
add = _example_core.add
sub = _example_core.sub
mul = _example_core.mul

__all__ = ["add", "sub", "mul"]
