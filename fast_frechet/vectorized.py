import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    M = np.empty((P + 1, Q + 1))
    M[0, :] = np.inf
    M[:, 0] = np.inf
    M[0, 0] = 0.0

    d = metric(p[:, np.newaxis], q[np.newaxis, :])

    for i in range(P):
        u = np.minimum(M[i, :-1], M[i, 1:])

        for j in range(Q):
            M[i + 1, j + 1] = max(min(M[i + 1, j], u[j]), d[i, j])

    return M[P, Q]
