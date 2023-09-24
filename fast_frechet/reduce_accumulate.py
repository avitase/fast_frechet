from functools import partial, reduce
from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, v):
    prev, d = v
    return max(min(acc, prev), d)


def frechet_next(acc, d):
    min_prev_row = np.minimum(acc[:-1], acc[1:])
    return list(accumulate(zip(min_prev_row, d), frechet_maxmin, initial=np.inf))


def frechet_distance(p, q, metric):
    init = np.maximum.accumulate(metric(p[0], q))
    init = np.insert(init, 0, np.inf)

    return reduce(frechet_next, map(partial(metric, q), p[1:]), init)[-1]
