from functools import partial, reduce
from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    v, d = x
    return max(min(acc, v), d)


def frechet_next(v, d):
    u = np.minimum(v[:-1], v[1:])

    init = max(v[0], d[0])
    return list(accumulate(zip(u, d[1:]), frechet_maxmin, initial=init))


def frechet_distance(p, q, metric):
    v = np.maximum.accumulate(metric(p[0], q))
    return reduce(frechet_next, map(partial(metric, q), p[1:]), v)[-1]
