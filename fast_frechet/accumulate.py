from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    u, d = x
    return max(min(acc, u), d)


def frechet_distance(p, q, metric):
    P = p.shape[0]

    v = np.maximum.accumulate(metric(p[0], q))
    v = np.insert(v, 0, np.inf)

    for i in range(1, P):
        d = metric(p[i], q)
        u = np.minimum(v[:-1], v[1:])

        v = list(accumulate(zip(u, d), frechet_maxmin, initial=np.inf))

    return v[-1]
