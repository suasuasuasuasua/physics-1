from __future__ import annotations

import physics_1 as m


def test_add():
    assert m.add(1, 2) == 3


def test_sub():
    assert m.sub(1, 2) == -1


def test_reduce_cpp():
    count = 1_000_0000
    target = 49999995000000.0
    nums = list(float(i) for i in range(count))
    assert m.reduce(nums, 0) == target


def test_reduce_python():
    count = 1_000_0000
    target = 49999995000000.0
    sum = 0
    for i in range(count):
        sum += i
    assert sum == target
