import numpy as np


def frechet_distance(p, q, *, metric):
    P = p.shape[0]
    Q = q.shape[0]
    ca = np.full((P, Q), -1.0)

    def c(i, j):
        if ca[i, j] > -1.0:
            return ca[i, j]

        d = metric(p[i], q[j])

        if i == 0 and j == 0:
            ca[i, j] = d
        elif i > 0 and j == 0:
            ca[i, j] = max(c(i - 1, 0), d)
        elif i == 0 and j > 0:
            ca[i, j] = max(c(0, j - 1), d)
        elif i > 0 and j > 0:
            ca[i, j] = max(min(c(i - 1, j), c(i - 1, j - 1), c(i, j - 1)), d)

        return ca[i, j]

    return c(P - 1, Q - 1)
