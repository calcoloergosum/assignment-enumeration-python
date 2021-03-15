"""Type aliases for semantic naming"""
from typing import Callable, Iterator, List, Tuple, TypeVar

import numpy as np

T = TypeVar("T")
Matching = List[Tuple[T, T]]
MatchingIndices = Tuple[np.ndarray, np.ndarray]
Edge = Tuple[T, T, float]

EnumerationAlgorithm = Callable[[List[Edge[T]]], Iterator[Matching[T]]]
CostMatrix = np.ndarray
