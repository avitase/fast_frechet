import numpy as np
import pytest

from fast_frechet import (
    accumulate,
    batched,
    branchless,
    compiled,
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


def generate_trajectory(n, *, dim, rng):
    x0 = rng.integers(-2, 2, size=(1, dim), endpoint=False)
    dx = rng.integers(-1, 1, size=(n, dim), endpoint=False)
    x = x0 + np.cumsum(dx, axis=0)

    if dim == 1:
        x = x.flatten()

    return x.astype(np.float64)


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
        compiled,
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
        compiled,
    ],
)
@pytest.mark.parametrize("P,Q", [(2, 2), (3, 4), (9, 4)])
@pytest.mark.parametrize("dim", [1, 2])
@pytest.mark.parametrize("seed", range(100))
def test_frechet(variant, P, Q, dim, seed):
    rng = np.random.default_rng(seed)

    p = generate_trajectory(P, dim=dim, rng=rng)
    q = generate_trajectory(Q, dim=dim, rng=rng)

    f = metric if dim > 1 else lambda p, q: np.abs(p - q)
    d_exp = vanilla.frechet_distance(p, q, metric=f)
    assert d_exp == vanilla.frechet_distance(q, p, metric=f)

    dpq = variant.frechet_distance(p, q, metric=f)
    dqp = variant.frechet_distance(q, p, metric=f)
    assert dpq == d_exp
    assert dqp == d_exp


@pytest.mark.parametrize("N,batch_size", [(1, 1), (2, 3), (3, 2), (20, 3)])
@pytest.mark.parametrize("dim", [1, 2])
@pytest.mark.parametrize("seed", range(100))
def test_batched_frechet(N, batch_size, dim, seed):
    rng = np.random.default_rng(seed)

    p = [
        generate_trajectory(n=n, dim=dim, rng=rng) for n in rng.integers(3, 10, size=N)
    ]
    q = generate_trajectory(n=4, dim=dim, rng=rng)

    f = metric if dim > 1 else lambda p, q: np.abs(p - q)
    d1 = [accumulate.frechet_distance(p[i], q, metric=f) for i in range(N)]
    d2 = batched.frechet_distance(p, q, f, batch_size=batch_size).tolist()

    assert d1 == d2
