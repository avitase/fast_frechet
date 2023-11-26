from functools import partial, reduce
from itertools import accumulate

import numpy as np


def dtw_min(acc, x):
    v, d = x
    return min(acc, v) + d


def dtw_next(v, d):
    u = np.minimum(v[:-1], v[1:])

    init = v[0] + d[0]
    return list(accumulate(zip(u, d[1:]), dtw_min, initial=init))


def dtw_distance(p, q, metric):
    v = np.cumsum(metric(p[0], q))
    return reduce(dtw_next, map(partial(metric, q), p[1:]), v)[-1]
