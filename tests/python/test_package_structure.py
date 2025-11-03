"""Test that the package structure is organized correctly."""
from __future__ import annotations


def test_top_level_imports():
    """Test that top-level package imports work correctly."""
    import physics_1

    # Top-level should have example and math packages
    assert hasattr(physics_1, "example")
    assert hasattr(physics_1, "math")


def test_example_package():
    """Test example package structure."""
    from physics_1 import example

    # example should have functions as a submodule
    assert hasattr(example, "functions")

    # example should expose add, sub, mul at package level
    assert hasattr(example, "add")
    assert hasattr(example, "sub")
    assert hasattr(example, "mul")

    # Test functions work
    assert example.add(1, 2) == 3
    assert example.sub(5, 3) == 2


def test_example_functions_module():
    """Test example.functions module."""
    from physics_1.example import functions

    # Functions should be available
    assert hasattr(functions, "add")
    assert hasattr(functions, "sub")
    assert hasattr(functions, "mul")

    # Test functions work
    assert functions.add(2, 3) == 5
    assert functions.sub(10, 4) == 6


def test_math_package():
    """Test math package structure."""
    from physics_1 import math

    # math should have constants and linalg as submodules
    assert hasattr(math, "constants")
    assert hasattr(math, "linalg")


def test_math_constants_module():
    """Test math.constants module."""
    from physics_1.math import constants
    import math as stdlib_math

    # Constants should be available
    assert hasattr(constants, "PI")
    assert hasattr(constants, "E")
    assert hasattr(constants, "deg_to_rad")

    # Test values
    assert constants.PI == stdlib_math.pi
    assert constants.E == stdlib_math.e

    # Test deg_to_rad function
    assert abs(constants.deg_to_rad(180) - stdlib_math.pi) < 0.0001
    assert abs(constants.deg_to_rad(90) - stdlib_math.pi / 2) < 0.0001


def test_math_linalg_package():
    """Test math.linalg package structure."""
    from physics_1.math import linalg

    # linalg should have vector as a submodule
    assert hasattr(linalg, "vector")

    # linalg should expose Vector2 at package level
    assert hasattr(linalg, "Vector2")

    # Test Vector2 works
    v = linalg.Vector2(3, 4)
    assert v.x() == 3
    assert v.y() == 4


def test_math_linalg_vector_module():
    """Test math.linalg.vector module."""
    from physics_1.math.linalg import vector

    # Vector2 should be available
    assert hasattr(vector, "Vector2")

    # Test Vector2 works
    v = vector.Vector2(1, 2)
    assert v.x() == 1
    assert v.y() == 2


def test_direct_imports():
    """Test that direct imports work."""
    # Direct imports should work
    from physics_1.example.functions import add, sub
    from physics_1.math.constants import PI, deg_to_rad
    from physics_1.math.linalg.vector import Vector2

    # Test they work
    assert add(1, 2) == 3
    assert sub(5, 2) == 3
    assert PI > 3.14
    assert deg_to_rad(180) > 3.14
    v = Vector2(1, 1)
    assert v.x() == 1
