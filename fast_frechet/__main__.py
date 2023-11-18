import sys
import timeit
from functools import partial

import numpy as np

from fast_frechet import (
    accumulate,
    batched,
    branchless,
    linear_memory,
    no_recursion,
    reduce_accumulate,
    vectorized,
)


def metric(p, q):
    dx = p[..., 0] - q[..., 0]
    dy = p[..., 1] - q[..., 1]
    return np.hypot(dx, dy)


def generate_trajectory(n, *, rng):
    xy0 = rng.integers(-2, 2, size=(1, 2), endpoint=False).astype(np.float64)
    dxy = rng.integers(-1, 1, size=(n, 2), endpoint=False).astype(np.float64)
    return xy0 + np.cumsum(dxy, axis=0)


def benchmark(f, *, n, rng):
    p = generate_trajectory(n, rng=rng)
    q = generate_trajectory(n, rng=rng)
    return min(timeit.repeat(lambda: f(p, q), repeat=3, number=1)) * 1_000


def benchmark_batched(f, *, n_low, n_high, N, rng):
    p = [generate_trajectory(n, rng=rng) for n in rng.integers(n_low, n_high, size=N)]
    q = generate_trajectory(rng.integers(n_low, n_high), rng=rng)
    return min(timeit.repeat(lambda: f(p, q), repeat=3, number=1)) * 1_000


def main(test_batched):
    rng = np.random.default_rng(42)

    if not test_batched:
        for v in [
            no_recursion,
            branchless,
            vectorized,
            linear_memory,
            accumulate,
            reduce_accumulate,
        ]:
            f = partial(v.frechet_distance, metric=metric)
            t = benchmark(f, n=500, rng=rng)
            print(f"{v.__name__.split('.')[-1]:>20}: {t:>4.0f} ms")

    else:
        N = 500
        n_low, n_high = 80, 120
        print(" Number of trajectories:", N)
        print(f"Length of trajectories: [{n_low}, {n_high}]")
        print("")

        f = lambda p, q: list(
            map(
                partial(reduce_accumulate.frechet_distance, q=q, metric=metric),
                p,
            )
        )
        t = benchmark_batched(f, n_low=n_low, n_high=n_high, N=N, rng=rng)
        print("reduce_accumulate (reference):".rjust(33), f"{t:>4.0f} ms")

        for batch_size in [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]:
            f = partial(batched.frechet_distance, metric=metric, batch_size=batch_size)
            t = benchmark_batched(
                partial(f, metric=metric), n_low=n_low, n_high=n_high, N=N, rng=rng
            )
            print(f"batch size={batch_size}:".rjust(33), f"{t:>4.0f} ms")


if __name__ == "__main__":
    main(test_batched=len(sys.argv) == 2 and sys.argv[1] == "--batched")
