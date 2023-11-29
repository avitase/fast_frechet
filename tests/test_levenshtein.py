from itertools import permutations

import numpy as np
import pytest

from fast_frechet.levenshtein import levenshtein_distance


def vanilla_levenshtein_distance(p, q):
    P = len(p)
    Q = len(q)

    d = np.zeros((P + 1, Q + 1), dtype=np.int64)
    d[1:, 0] = np.arange(1, P + 1)
    d[0, 1:] = np.arange(1, Q + 1)

    for j in range(1, Q + 1):
        for i in range(1, P + 1):
            substitution_cost = 0 if p[i - 1] == q[j - 1] else 1
            d[i, j] = min(
                [
                    d[i - 1, j] + 1,  # deletion
                    d[i, j - 1] + 1,  # insertion
                    d[i - 1, j - 1] + substitution_cost,  # substitution
                ]
            )

    return d[P, Q]


@pytest.mark.parametrize(
    "p, q, d_exp",
    [
        ("a", "b", 1),
        ("a", "ab", 1),
        ("ab", "ab", 0),
        ("ab", "ac", 1),
        ("ab", "cb", 1),
        ("ab", "ba", 2),
        ("kitten", "kitten", 0),
        ("kitten", "sitten", 1),
        ("kitten", "sittes", 2),
        ("kitten", "sityteng", 3),
        ("kitten", "sittYing", 4),
        ("rosettacode", "raisethysword", 8),
        ("kitten", "kittenaaaaaaaaaaaaaaaaa", 17),
        *[
            (p, q, vanilla_levenshtein_distance(p, q))
            for p in map("".join, permutations("ab"))
            for q in map("".join, permutations("abc"))
        ],
        *[
            (p, q, vanilla_levenshtein_distance(p, q))
            for p in map("".join, permutations("ab"))
            for q in map("".join, permutations("acd"))
        ],
    ],
)
def test_levenshtein(p, q, d_exp):
    assert vanilla_levenshtein_distance(p, q) == d_exp

    dpq = levenshtein_distance(p, q)
    dqp = levenshtein_distance(q, p)
    assert dpq == d_exp
    assert dqp == d_exp
