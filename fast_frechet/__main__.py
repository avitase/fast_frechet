import timeit
from functools import partial

import numpy as np

from fast_frechet import (
    accumulate,
    branchless,
    compiled,
    linear_memory,
    no_recursion,
    reduce_accumulate,
    vectorized,
)


def metric(a, b):
    dx = a[..., 0] - b[..., 0]
    dy = a[..., 1] - b[..., 1]
    return np.hypot(dx, dy)


def generate_trajectory(n, *, rng):
    xy0 = rng.integers(-2, 2, size=(1, 2), endpoint=False).astype(np.float64)
    dxy = rng.integers(-1, 1, size=(n, 2), endpoint=False).astype(np.float64)
    return xy0 + np.cumsum(dxy, axis=0)


def benchmark(f, *, n, rng):
    p = generate_trajectory(n, rng=rng)
    q = generate_trajectory(n, rng=rng)
    return min(timeit.repeat(lambda: f(p, q), repeat=3, number=1))


def main(n=1024, seed=42):
    print(f"{n=}, {seed=}\n")

    rng = np.random.default_rng(seed)
    for v in [
        no_recursion,
        branchless,
        vectorized,
        linear_memory,
        accumulate,
        reduce_accumulate,
        compiled,
    ]:
        f = partial(v.frechet_distance, metric=metric)
        t = benchmark(partial(f, metric=metric), n=n, rng=rng) * 1_000
        print(f"{v.__name__.split('.')[-1]:>20}: {t:4.0f} ms")


if __name__ == "__main__":
    main()
