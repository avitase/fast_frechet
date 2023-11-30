from itertools import accumulate

import numpy as np


def frechet_maxmin(acc, x):
    u, d = x
    return np.maximum(np.minimum(acc, u), d)


def frechet_distance(p, q, metric, *, batch_size):
    N = len(p)
    P = np.array(list(map(len, p)))

    rho = np.full(batch_size, 1, dtype=np.int64)
    mu = np.minimum(np.arange(batch_size), N - 1)

    p0 = np.array([p[min(i, N - 1)][0] for i in range(batch_size)])
    v = np.maximum.accumulate(metric(p0[np.newaxis], q[:, np.newaxis]))

    dF = np.empty(N)
    i = 0
    while i < max(batch_size, N):
        while not np.any(rho == P[mu]):
            u = np.minimum(v[:-1], v[1:])

            d = metric(
                np.array(
                    [[p[j1][j2] for j1, j2 in zip(mu, np.minimum(rho, P[mu] - 1))]]
                ),
                q[:, np.newaxis],
            )
            v[0] = np.maximum(v[0], d[0])
            v[1:] = d[1:]
            v = list(accumulate(zip(u, v[1:]), frechet_maxmin, initial=v[0]))
            v = np.array(v)

            rho += 1

        for j in [k for k in range(batch_size) if rho[k] == P[mu[k]]]:
            dF[mu[j]] = v[-1, j]
            i += 1

            rho[j] += 1
            if i + batch_size - 1 < N:
                mu[j] = i + batch_size - 1
                rho[j] = 1

                v[:, j] = np.maximum.accumulate(metric(p[mu[j]][0], q))

    return dF
