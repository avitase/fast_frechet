import numpy as np
import pytest

from fast_frechet.dtw import dtw_distance


def metric(a, b):
    return np.abs(a - b)


@pytest.mark.parametrize(
    "p, q, d_exp",
    [([0.0, 2.0, 0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 0.5, 2.0, 0.0, 1.0, 0.0], 0.5)],
)
def test_dtw(p, q, d_exp):
    p = np.array(p)
    q = np.array(q)

    dpq = dtw_distance(p, q, metric=metric)
    dqp = dtw_distance(q, p, metric=metric)
    assert dpq == d_exp
    assert dqp == d_exp
