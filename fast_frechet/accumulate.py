from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    v, d = x
    return max(min(acc, v), d)


def frechet_distance(p, q, metric):
    P = p.shape[0]

    v = np.maximum.accumulate(metric(p[0], q))
    for i in range(1, P):
        u = np.minimum(v[:-1], v[1:])

        v[0] = max(v[0], metric(p[i], q[0]))
        v[1:] = metric(p[i], q[1:])
        v = list(accumulate(zip(u, v[1:]), frechet_maxmin, initial=v[0]))

    return v[-1]
