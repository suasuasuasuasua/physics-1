from __future__ import annotations

from physics_1 import linalg


def test_Vector2D_DefaultConstructor():
    x = linalg.Vector2D()

    assert x.x() == 0 and x.y() == 0


def test_Vector2D_Constructor():
    x = linalg.Vector2D(1, 10)

    assert x.x() == 1 and x.y() == 10


def test_Vector2D_Add():
    x = linalg.Vector2D(1, 2)
    y = linalg.Vector2D(3, 5)

    z = x + y
    assert z.x() == 4 and z.y() == 7


def test_Vector2D_SelfAdd():
    x = linalg.Vector2D(1, 2)
    y = linalg.Vector2D(3, 5)

    x += y
    assert x.x() == 4 and x.y() == 7


def test_Vector2D_Sub():
    x = linalg.Vector2D(1, 2)
    y = linalg.Vector2D(3, 5)

    z = x - y
    assert z.x() == -2 and z.y() == -3


def test_Vector2D_SelfSub():
    x = linalg.Vector2D(1, 2)
    y = linalg.Vector2D(3, 5)

    x -= y
    assert x.x() == -2 and x.y() == -3
