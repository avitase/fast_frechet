from itertools import accumulate

import numpy as np


def metric(p, q):
    return np.where(p == q, 0, 1)


def levenshtein_min(acc, x):
    return min(acc + 1, x)


def levenshtein_distance(p, q):
    p = np.array(list(p))
    q = np.array(list(q))

    P = len(p)
    Q = len(q)

    v = list(accumulate(metric(p[0], q) + np.arange(Q), levenshtein_min))
    v = np.array(v)

    for i in range(1, P):
        d = metric(p[i], q)
        u = np.minimum(v[:-1] + d[1:], v[1:] + 1)

        init = min(d[0] + i, v[0] + 1)
        v = list(accumulate(u, levenshtein_min, initial=init))
        v = np.array(v)

    return v[-1]
