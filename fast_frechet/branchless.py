import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    ca = np.empty((P + 1, Q + 1))
    ca[0, :] = np.inf
    ca[:, 0] = np.inf
    ca[0, 0] = 0.0

    for i in range(P):
        for j in range(Q):
            d = metric(p[i], q[j])
            ca[i + 1, j + 1] = max(min(ca[i + 1, j], ca[i, j + 1], ca[i, j]), d)

    return ca[P, Q]
