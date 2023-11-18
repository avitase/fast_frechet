import numpy as np


def frechet_distance(p, q, metric):
    P = p.shape[0]
    Q = q.shape[0]

    v = np.maximum.accumulate(metric(p[0], q))
    v = np.insert(v, 0, np.inf)

    for i in range(1, P):
        u = np.minimum(v[:-1], v[1:])
        d = metric(p[i], q)

        for j in range(Q):
            v[j + 1] = max(min(v[j], u[j]), d[j])

    return v[Q]
