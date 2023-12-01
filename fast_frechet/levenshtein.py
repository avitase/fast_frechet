from functools import partial, reduce
from itertools import accumulate

import numpy as np


def metric(p, q):
    return np.where(p == q, 0, 1)


def levenshtein_min(acc, x):
    return min(acc + 1, x)


def levenshtein_next(acc, x):
    acc = np.array(acc)

    i, d = x
    acc[1:] = np.minimum(acc[:-1] + d[1:], acc[1:] + 1)
    acc[0] = min(i + d[0], acc[0] + 1)
    return list(accumulate(acc, levenshtein_min))


def levenshtein_distance(p, q):
    p = np.array(list(p))
    q = np.array(list(q))

    iP = np.arange(len(p))
    iQ = np.arange(len(q))

    d = map(partial(metric, q), p)

    init = list(accumulate(iQ + next(d), levenshtein_min))
    return reduce(levenshtein_next, zip(iP[1:], d), init)[-1]
