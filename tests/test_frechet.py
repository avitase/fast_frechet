import numpy as np
import pytest

from fast_frechet import (
    accumulate,
    batched,
    branchless,
    linear_memory,
    no_recursion,
    reduce_accumulate,
    vanilla,
    vectorized,
)


def metric(p, q):
    dx = p[..., 0] - q[..., 0]
    dy = p[..., 1] - q[..., 1]

    return dx**2 + dy**2


def generate_trajectory(n, *, rng):
    xy0 = rng.integers(-2, 2, size=(1, 2), endpoint=False)
    dxy = rng.integers(-1, 1, size=(n, 2), endpoint=False)
    xy = xy0 + np.cumsum(dxy, axis=0)
    return xy.astype(np.float64)


@pytest.mark.parametrize(
    "variant",
    [
        vanilla,
        no_recursion,
        vectorized,
        branchless,
        linear_memory,
        accumulate,
        reduce_accumulate,
    ],
)
def test_simple_example(variant):
    p = np.array([[1, 2], [3, 4]])
    q = np.array([[2, 1], [3, 3], [5, 5]])

    d = variant.frechet_distance(
        p, q, metric=lambda a, b: np.hypot(a[..., 0] - b[..., 0], a[..., 1] - b[..., 1])
    )
    assert d == pytest.approx(np.sqrt(5.0))


@pytest.mark.parametrize(
    "variant",
    [
        no_recursion,
        vectorized,
        branchless,
        linear_memory,
        accumulate,
        reduce_accumulate,
    ],
)
@pytest.mark.parametrize("P,Q", [(2, 2), (3, 4), (9, 4)])
@pytest.mark.parametrize("seed", range(100))
def test_frechet(variant, P, Q, seed):
    rng = np.random.default_rng(seed)

    p = generate_trajectory(P, rng=rng)
    q = generate_trajectory(Q, rng=rng)

    d1 = vanilla.frechet_distance(p, q, metric=metric)
    d2 = variant.frechet_distance(p, q, metric=metric)
    assert d1 == d2


@pytest.mark.parametrize("N,batch_size", [(1, 1), (2, 3), (3, 2), (20, 3)])
@pytest.mark.parametrize("seed", range(100))
def test_batched_frechet(N, batch_size, seed):
    rng = np.random.default_rng(seed)

    p = [generate_trajectory(n=n, rng=rng) for n in rng.integers(3, 10, size=N)]
    q = generate_trajectory(n=4, rng=rng)

    d1 = [accumulate.frechet_distance(p[i], q, metric=metric) for i in range(N)]
    d2 = batched.frechet_distance(p, q, metric, batch_size=batch_size).tolist()

    assert d1 == d2
