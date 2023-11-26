import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    v = metric(p[0], q)
    v = np.maximum.accumulate(v)

    for i in range(1, P):
        u = np.minimum(v[:-1], v[1:])

        v[0] = max(v[0], metric(p[i], q[0]))
        v[1:] = metric(p[i], q[1:])
        for j in range(1, Q):
            v[j] = max(min(v[j - 1], u[j - 1]), v[j])

    return v[-1]
