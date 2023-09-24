from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, v):
    prev, d = v
    return max(min(acc, prev), d)


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    row = np.maximum.accumulate(metric(p[0], q))
    row = np.insert(row, 0, np.inf)

    for i in range(1, P):
        d = metric(p[i], q)
        min_prev_row = np.minimum(row[:-1], row[1:])

        row = accumulate(zip(min_prev_row, d), frechet_maxmin, initial=np.inf)
        row = list(row)

    return row[Q]
