from __future__ import annotations

import math

from physics_1 import linalg


def test_Vector2_DefaultConstructor():
    x = linalg.Vector2()

    assert x.x == 0 and x.y == 0


def test_Vector2_Constructor():
    x = linalg.Vector2(1, 10)

    assert x.x == 1 and x.y == 10


def test_Vector2_Add():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    z = x + y
    assert z.x == 4 and z.y == 7


def test_Vector2_AddSelf():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x += y
    assert x.x == 4 and x.y == 7


def test_Vector2_Sub():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    z = x - y
    assert z.x == -2 and z.y == -3


def test_Vector2_SubSelf():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x -= y
    assert x.x == -2 and x.y == -3


def test_Vector2_Mul():
    x = linalg.Vector2(1, 2)
    scalar = 4.0

    z = x * scalar
    assert z.x == 4 and z.y == 8


def test_Vector2_MulSelf():
    x = linalg.Vector2(1, 2)
    scalar = 4.0

    x *= scalar
    assert x.x == 4 and x.y == 8


def test_Vector2_Div():
    x = linalg.Vector2(8, 12)
    scalar = 4.0

    z = x / scalar
    assert z.x == 2 and z.y == 3


def test_Vector2_DivSelf():
    x = linalg.Vector2(8, 12)
    scalar = 4.0

    x /= scalar
    assert x.x == 2 and x.y == 3


def test_Vector2_toString():
    x = linalg.Vector2(1, 2)

    assert str(x) == "X: 1 Y: 2"


def test_Vector2_Negation():
    x = linalg.Vector2(3, -4)

    y = -x
    assert y.x == -3 and y.y == 4


def test_Vector2_Equal():
    x = linalg.Vector2(3, 6)
    y = linalg.Vector2(3, 6)

    assert x == y


def test_Vector2_NotEqual():
    x = linalg.Vector2(3, 6)
    y = linalg.Vector2(5, 7)

    assert x != y


def test_Vector2_Mag():
    x = linalg.Vector2(3, 4)

    assert x.mag() == 25


def test_Vector2_Unit():
    x = linalg.Vector2(3, 4)
    y = x.unit()

    assert abs(y.x - 0.12) < 0.001 and abs(y.y - 0.16) < 0.001


def test_Vector2_Angle():
    x = linalg.Vector2(1, 1)

    assert abs(x.angle() - math.pi / 4) < 0.001


def test_Vector2_FromMagAng():
    magnitude = 2
    angle = math.pi / 6

    v = linalg.Vector2.from_mag_ang(magnitude, angle)
    assert abs(v.x - math.sqrt(3)) < 0.001 and abs(v.y - 1.0) < 0.001


def test_Vector2_ScalarMul():
    x = linalg.Vector2(2, 3)
    scalar = 4.0

    z = scalar * x
    assert z.x == 8 and z.y == 12
