import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    ca = np.empty((P + 1, Q + 1))
    ca[0, :] = np.inf
    ca[:, 0] = np.inf
    ca[0, 0] = 0.0

    d = metric(p[:, np.newaxis], q[np.newaxis, :])

    for i in range(P):
        min_prev_row = np.minimum(ca[i, :-1], ca[i, 1:])

        for j in range(Q):
            ca[i + 1, j + 1] = max(min(ca[i + 1, j], min_prev_row[j]), d[i, j])

    return ca[P, Q]
