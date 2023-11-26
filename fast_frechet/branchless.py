import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    d = metric(p[:, np.newaxis], q[np.newaxis])
    d[:, 0] = np.maximum.accumulate(d[:, 0])
    d[0, :] = np.maximum.accumulate(d[0, :])

    for i in range(1, P):
        for j in range(1, Q):
            d[i, j] = max(min(d[i - 1, j], d[i - 1, j - 1], d[i, j - 1]), d[i, j])

    return d[P - 1, Q - 1]
