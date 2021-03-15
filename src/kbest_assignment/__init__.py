from .naive import *
from ._types import *

from .lsap import calculate_assignment


ALGORITHMS: List[EnumerationAlgorithm[T]] = [
    naive
]
