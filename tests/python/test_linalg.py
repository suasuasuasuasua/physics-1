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


def test_Vector2_SelfAdd():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x += y
    assert x.x() == 4 and x.y() == 7


def test_Vector2_Sub():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    z = x - y
    assert z.x() == -2 and z.y() == -3


def test_Vector2_SelfSub():
    x = linalg.Vector2(1, 2)
    y = linalg.Vector2(3, 5)

    x -= y
    assert x.x() == -2 and x.y() == -3
