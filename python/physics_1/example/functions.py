"""Functions module with basic mathematical operations."""
from __future__ import annotations

def _get_example_core():
    """Lazy import of _core.example to avoid circular imports."""
    try:
        # Try importing from _core first (when _core is standalone)
        from _core import example
        return example
    except ImportError:
        pass
    
    # Try importing from physics_1._core
    try:
        from physics_1._core import example
        return example
    except ImportError:
        pass
    
    # If all else fails, try relative import
    from .._core import example
    return example

_example_core = _get_example_core()

# Re-export functions from the C++ module
add = _example_core.add
sub = _example_core.sub
mul = _example_core.mul

__all__ = ["add", "sub", "mul"]
