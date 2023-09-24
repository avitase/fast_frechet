import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]
    ca = np.empty((P, Q))

    for i in range(P):
        for j in range(Q):
            d = metric(p[i], q[j])

            if i == 0 and j == 0:
                ca[i, j] = d
            elif i > 0 and j == 0:
                ca[i, j] = max(ca[i - 1, 0], d)
            elif i == 0 and j > 0:
                ca[i, j] = max(ca[0, j - 1], d)
            elif i > 0 and j > 0:
                ca[i, j] = max(min(ca[i, j - 1], ca[i - 1, j], ca[i - 1, j - 1]), d)

    return ca[P - 1, Q - 1]
