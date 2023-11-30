from functools import partial, reduce
from itertools import accumulate

import numpy as np


def dtw_min(acc, x):
    v, d = x
    return min(acc, v) + d


def dtw_next(v, d):
    v[1:] = np.minimum(v[:-1], v[1:])

    init = v[0] + d[0]
    return list(accumulate(zip(v[1:], d[1:]), dtw_min, initial=init))


def dtw_distance(p, q, metric):
    d = map(partial(metric, q), p)
    init = np.cumsum(next(d))
    return reduce(dtw_next, d, init)[-1]
