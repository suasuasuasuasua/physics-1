from __future__ import annotations

from physics_1 import linalg


def test_Vector2_DefaultConstructor():
    x = linalg.Vector2()

    assert x.x() == 0 and x.y() == 0


def test_Vector2_Constructor():
    x = linalg.Vector2(1, 10)

    assert x.x() == 1 and x.y() == 10


def test_Vector2_Add():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    z = x + y
    assert z.x() == 4 and z.y() == 7


def test_Vector2_AddSelf():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x += y
    assert x.x() == 4 and x.y() == 7


def test_Vector2_Sub():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    z = x - y
    assert z.x() == -2 and z.y() == -3


def test_Vector2_SubSelf():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x -= y
    assert x.x() == -2 and x.y() == -3


def test_Vector2_Mul():
    x = linalg.Vector2(1, 2)
    scalar = 4.0

    z = x * scalar
    assert z.x() == 4 and z.y() == 8


def test_Vector2_MulSelf():
    x = linalg.Vector2(1, 2)
    scalar = 4.0

    x *= scalar
    assert x.x() == 4 and x.y() == 8


def test_Vector2_Div():
    x = linalg.Vector2(8, 12)
    scalar = 4.0

    z = x / scalar
    assert z.x() == 2 and z.y() == 3


def test_Vector2_DivSelf():
    x = linalg.Vector2(8, 12)
    scalar = 4.0

    x /= scalar
    assert x.x() == 2 and x.y() == 3


def test_Vector2_toString():
    x = linalg.Vector2(1, 2)

    assert str(x) == "X: 1 Y: 2"


def test_Vector2_Negation():
    x = linalg.Vector2(3, -4)

    y = -x
    assert y.x() == -3 and y.y() == 4
