import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]
    M = np.empty((P, Q))

    d = metric(p[:, np.newaxis], q[np.newaxis])

    for i in range(P):
        for j in range(Q):
            if i == 0 and j == 0:
                M[i, j] = d[i, j]
            elif i > 0 and j == 0:
                M[i, j] = max(M[i - 1, 0], d[i, j])
            elif i == 0 and j > 0:
                M[i, j] = max(M[0, j - 1], d[i, j])
            elif i > 0 and j > 0:
                M[i, j] = max(min(M[i, j - 1], M[i - 1, j], M[i - 1, j - 1]), d[i, j])

    return M[P - 1, Q - 1]
