# Fast Discrete Fréchet Distance 

This is Python package that provides a collection of different implementations for calculating the discrete [Fréchet distance](https://en.wikipedia.org/wiki/Fr%C3%A9chet_distance) between two polygonal curves.

As a baseline, referred to as [`vanilla`][vanilla], we implement the proposed algorithm by [Eiter and Manilla (1994)][vanilla].
Starting from here, we subsequently fix several of its shortcomings.
More precisely, 

1. [`vanilla`](fast_frechet/vanilla.py): The baseline implementation as proposed in [_Computing Discrete Fréchet Distance_ by T. Eiter and H. Mannila (1994)][vanilla]
1. [`no_recursion`](fast_frechet/no_recursion.py): A formulation w/o recursion.
1. [`vectorized`](fast_frechet/vectorized.py): A vectorized implementation that calculates the distance matrix within a single [NumPy](https://numpy.org/) call.
1. [`branchless`](fast_frechet/branchless.py): A variant w/o branches.
1. [`linear_memory`](fast_frechet/linear_memory.py): This formulation reduces the quadratic memory footprint to a linear one.
1. [`accumulate`](fast_frechet/accumulate.py): Formulation using a scan operation.
1. [`reduce_accumulate`](fast_frechet/reduce_accumulate.py): Formulation using a fold operation.
1. [`compiled`](fast_frechet/compiled.py): Variant of [`reduce_accumulate`](fast_frechet/reduce_accumulate.py) using the [Numba library](https://numba.pydata.org/) for JIT compilation of the innermost loop.
1. [`batched`](fast_frechet/batched.py): A variant of [`accumulate`](fast_frechet/accumulate.py) that operates on batches.

Implementations of all these variants can be found under [`fast_frechet/`](fast_frechet/) or by simply clicking on the listed names above.

## Installation

```bash
# production installation
$ pip install -r requirements.txt
$ pip install fast_frechet

# development installation
$ pip install -e .[dev]
$ pre-commit install
```

## Usage

The snippet below estimates the Fréchet distance between the polygonal curves `p` and `q` using the Euclidean distance as a metric to measure distances between points:

```python
>>> from fast_frechet.linear_memory import frechet_distance

>>> p = np.array([[1, 2], [3, 4]])
>>> q = np.array([[2, 1], [3, 3], [5, 5]])

>>> frechet_distance(p, q, metric=lambda a, b: np.hypot(a[..., 0] - b[..., 0], a[..., 1] - b[..., 1]))
2.23606797749979
```

For invoking the [benchmark script](fast_frechet/__main__.py), run:

```bash
$ python fast_frechet
Length of trajectory = 1024

        no_recursion: 2471 ms
          vectorized:  680 ms
          branchless:  602 ms
       linear_memory:  411 ms
          accumulate:  296 ms
   reduce_accumulate:  292 ms
            compiled:   11 ms
```
(Note that we don't even try to benchmark the [`vanilla`](fast_frechet/vanilla.py) version here, as it already crashes for polygonal curves with a few hundred points due to its recursive nature.)

To see the performance of the batched variant, run:

```bash
$ python fast_frechet --batched
Number of trajectories = 1024
Length of trajectories ~ Binom(p=0.2, N=1024)

   reduce_accumulate (reference): 13016 ms
                    batch size=4: 11550 ms
                    batch size=8:  5966 ms
                   batch size=16:  3243 ms
                   batch size=32:  1870 ms
                   batch size=64:  1204 ms
                  batch size=128:   877 ms
                  batch size=256:   750 ms
                  batch size=512:   764 ms
                 batch size=1024:   715 ms
                 batch size=2048:  1274 ms
```
The performance depends on the chosen batch size. In particular, if the batch size becomes larger as the number of trajectories the performance will deteriorate.

[vanilla]: http://www.kr.tuwien.ac.at/staff/eiter/et-archive/cdtr9464.pdf
