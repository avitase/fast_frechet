from itertools import accumulate

import numpy as np


def levenshtein_min(acc, x):
    u, d = x
    return min(1 + acc, 1 + u, d)


def levenshtein_distance(p, q):
    p = np.array(list(p))
    q = np.array(list(q))

    P = len(p)
    Q = len(q)

    v = np.arange(Q + 1)
    for i in range(P):
        d = np.where(p[i] == q, v[:-1], np.inf)
        u = np.minimum(v[:-1], v[1:])

        v = list(accumulate(zip(u, d), levenshtein_min, initial=i + 1))

    return v[-1]


if __name__ == "__main__":
    assert levenshtein_distance("kitten", "kitten") == 0
    assert levenshtein_distance("kitten", "sitten") == 1
    assert levenshtein_distance("kitten", "sittes") == 2
    assert levenshtein_distance("kitten", "sityteng") == 3
    assert levenshtein_distance("kitten", "sittYing") == 4
    assert levenshtein_distance("rosettacode", "raisethysword") == 8
    assert levenshtein_distance("kitten", "kittenaaaaaaaaaaaaaaaaa") == 17
    assert levenshtein_distance("kittenaaaaaaaaaaaaaaaaa", "kitten") == 17
