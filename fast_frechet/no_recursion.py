import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]
    M = np.empty((P, Q))

    for i in range(P):
        for j in range(Q):
            d = metric(p[i], q[j])

            if i == 0 and j == 0:
                M[i, j] = d
            elif i > 0 and j == 0:
                M[i, j] = max(M[i - 1, 0], d)
            elif i == 0 and j > 0:
                M[i, j] = max(M[0, j - 1], d)
            elif i > 0 and j > 0:
                M[i, j] = max(min(M[i, j - 1], M[i - 1, j], M[i - 1, j - 1]), d)

    return M[P - 1, Q - 1]
