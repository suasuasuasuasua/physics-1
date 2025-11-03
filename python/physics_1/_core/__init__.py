"""Import the actual _core C++ extension module."""
# Import everything from the actual _core module
import sys

# Try to import _core from the build directory or site-packages
try:
    import _core as _real_core
except ImportError as e:
    raise ImportError(
        f"Cannot import _core C++ extension module. "
        f"Make sure the module is built and accessible. Error: {e}"
    )

# Re-export everything from the real _core module
__doc__ = _real_core.__doc__
__version__ = getattr(_real_core, '__version__', 'dev')
example = _real_core.example
math = _real_core.math

# Register submodules in sys.modules so they can be imported
sys.modules['physics_1._core.example'] = example
sys.modules['physics_1._core.example.functions'] = example.functions
sys.modules['physics_1._core.math'] = math
sys.modules['physics_1._core.math.constants'] = math.constants
sys.modules['physics_1._core.math.linalg'] = math.linalg
sys.modules['physics_1._core.math.linalg.vector'] = math.linalg.vector

__all__ = ['__doc__', '__version__', 'example', 'math']
