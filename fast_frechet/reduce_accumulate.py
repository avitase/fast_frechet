from functools import partial, reduce
from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    u, d = x
    return max(min(acc, u), d)


def frechet_next(acc, x):
    u = np.minimum(acc[:-1], acc[1:])
    return list(accumulate(zip(u, x), frechet_maxmin, initial=np.inf))


def frechet_distance(p, q, metric):
    init = np.maximum.accumulate(metric(p[0], q))
    init = np.insert(init, 0, np.inf)

    return reduce(frechet_next, map(partial(metric, q), p[1:]), init)[-1]
