import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    M = np.empty((P + 1, Q + 1))
    M[0, :] = np.inf
    M[:, 0] = np.inf
    M[0, 0] = 0.0

    for i in range(P):
        for j in range(Q):
            d = metric(p[i], q[j])
            M[i + 1, j + 1] = max(min(M[i + 1, j], M[i, j + 1], M[i, j]), d)

    return M[P, Q]
