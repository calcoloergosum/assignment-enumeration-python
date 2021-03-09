"""Basic tests"""
from kbest_assignment import naive


def test_basic():
    """Simple test"""
    edges = [
        (11, 21, 1),
        (11, 22, 1),
        (12, 21, 2),
        (12, 22, 1),
    ]
    assert list(naive(edges)) == [
        [(11, 21), (12, 22)],
        [(11, 22), (12, 21)],
    ]
