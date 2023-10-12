from functools import partial, reduce

import numba
import numpy as np


@numba.njit
def frechet_next(acc, d):
    u = np.minimum(acc[:-1], acc[1:])

    Q = len(d)
    v = np.empty(Q + 1)
    v[0] = np.inf
    for j in range(Q):
        v[j + 1] = max(min(v[j], u[j]), d[j])

    return v


def frechet_distance(p, q, metric):
    init = np.maximum.accumulate(metric(p[0], q))
    init = np.insert(init, 0, np.inf)

    return reduce(frechet_next, map(partial(metric, q), p[1:]), init)[-1]
