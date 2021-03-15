from typing import List, Tuple, TypeVar, Callable, Iterator

T = TypeVar("T")
Matching = List[Tuple[T, T]]
Edge = Tuple[T, T, float]

EnumerationAlgorithm = Callable[[List[Edge[T]]], Iterator[Matching[T]]]
