from __future__ import annotations

from physics_1.example import functions as m


def test_add():
    assert m.add(1, 2) == 3


def test_sub():
    assert m.sub(1, 2) == -1
