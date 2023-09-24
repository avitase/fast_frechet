from functools import partial, reduce

import numba
import numpy as np


@numba.njit
def frechet_next(acc, d):
    min_prev_row = np.minimum(acc[:-1], acc[1:])

    Q = len(d)
    row = np.empty(Q + 1)
    row[0] = np.inf
    for j in range(Q):
        row[j + 1] = max(min(row[j], min_prev_row[j]), d[j])

    return row


def frechet_distance(p, q, metric):
    init = np.maximum.accumulate(metric(p[0], q))
    init = np.insert(init, 0, np.inf)

    return reduce(frechet_next, map(partial(metric, q), p[1:]), init)[-1]
