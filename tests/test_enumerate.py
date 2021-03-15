import itertools as it

import numpy as np
import pytest
from kbest_assignment import enumerate_kbest


@pytest.mark.parametrize('size', [5,] * 10)
def test_linear_sum_assignment(size: int) -> None:
    cost_matrix = np.random.random((size, size))
    solutions = list(enumerate_kbest(cost_matrix, ignore_same_value=True))

    # solution count
    assert len(solutions) == np.math.factorial(size)

    # solution sort
    solutions_sorted = sorted(solutions, key=lambda x: cost_matrix[x].sum())
    assert solutions == solutions_sorted

    # regression with brute-force
    bf_costs = sorted(cost_matrix[range(size), js].sum() for js in it.permutations(range(size)))
    solution_costs = [cost_matrix[s].sum() for s in solutions]

    np.testing.assert_allclose(bf_costs, solution_costs)
