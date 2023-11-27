from itertools import accumulate

import numpy as np


def metric(a, b):
    return np.where(a == b, 0, np.inf)


def levenshtein_min(acc, x):
    u, d = x
    return min(1 + acc, 1 + u, d)


def levenshtein_distance(p, q):
    p = np.array(list(p))
    q = np.array(list(q))

    P = len(p)
    Q = len(q)

    v = np.minimum(1, metric(p[0], q)) + np.arange(Q)

    for i in range(1, P):
        u = np.minimum(v[:-1], v[1:])
        d = metric(p[i], q)

        init = 1 + min(1 + i, u[0], d[0])
        v = list(accumulate(zip(u, d[1:] + v[:-1]), levenshtein_min, initial=init))

    return v[-1]
