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
    v = np.insert(v, 0, 1)

    for i in range(1, P):
        d = metric(p[i], q)
        u = np.minimum(v[:-1], v[1:])

        v = list(accumulate(zip(u, d + v[:-1]), levenshtein_min, initial=i + 1))

    return v[-1]
