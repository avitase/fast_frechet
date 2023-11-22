from functools import partial, reduce
from itertools import accumulate

import numpy as np


def dtw_min(acc, x):
    u, d = x
    return min(acc, u) + d


def dtw_next(acc, x):
    u = np.minimum(acc[:-1], acc[1:])
    return list(accumulate(zip(u, x), dtw_min, initial=np.inf))


def dtw_distance(p, q, metric):
    v = np.cumsum(metric(p[0], q))
    v = np.insert(v, 0, np.inf)

    return reduce(dtw_next, map(partial(metric, q), p[1:]), v)[-1]
