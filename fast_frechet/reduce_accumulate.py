from functools import partial, reduce
from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    v, d = x
    return max(min(acc, v), d)


def frechet_next(v, d):
    v[1:] = np.minimum(v[:-1], v[1:])

    init = max(v[0], d[0])
    return list(accumulate(zip(v[1:], d[1:]), frechet_maxmin, initial=init))


def frechet_distance(p, q, metric):
    d = map(partial(metric, q), p)
    init = np.maximum.accumulate(next(d))
    return reduce(frechet_next, d, init)[-1]
