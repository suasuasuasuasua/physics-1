from __future__ import annotations

from phys.example import functions


def test_add():
    assert functions.add(1, 2) == 3


def test_sub():
    assert functions.sub(1, 2) == -1
