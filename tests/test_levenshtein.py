import pytest

from fast_frechet.levenshtein import levenshtein_distance


@pytest.mark.parametrize(
    "p, q, d_exp",
    [
        ("kitten", "kitten", 0),
        ("kitten", "sitten", 1),
        ("kitten", "sittes", 2),
        ("kitten", "sityteng", 3),
        ("kitten", "sittYing", 4),
        ("rosettacode", "raisethysword", 8),
        ("kitten", "kittenaaaaaaaaaaaaaaaaa", 17),
        ("kittenaaaaaaaaaaaaaaaaa", "kitten", 17),
    ],
)
def test_levenshtein(p, q, d_exp):
    d = levenshtein_distance(p, q)
    assert d == d_exp
