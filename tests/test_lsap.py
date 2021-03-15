import kbest_assignment
import numpy as np

def test_lsap():
    cost_matrix = np.random.random((3, 3))
    _is, _js, _us, _vs = kbest_assignment.lsap.calculate_assignment(cost_matrix)
    reduced_cost_matrix = cost_matrix - _us[:, None] - _vs[None, :]
    assert np.all(reduced_cost_matrix > - 1e-50)
