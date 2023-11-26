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
        no_recursion:  712 ms
          vectorized:  210 ms
          branchless:  188 ms
       linear_memory:  125 ms
          accumulate:  100 ms
   reduce_accumulate:  100 ms
```
(Note that we don't even try to benchmark the [`vanilla`](fast_frechet/vanilla.py) version here, as it already crashes for polygonal curves with a few hundred points due to its recursive nature.)

To see the performance of the batched variant, run:

```bash
$ python fast_frechet --batched
 Number of trajectories: 500
Length of trajectories: [80, 120]

   reduce_accumulate (reference): 2464 ms
                    batch size=4: 2036 ms
                    batch size=8: 1156 ms
                   batch size=16:  608 ms
                   batch size=32:  397 ms
                   batch size=64:  227 ms
                  batch size=128:  193 ms
                  batch size=256:  137 ms
                  batch size=512:  148 ms
                 batch size=1024:  248 ms
                 batch size=2048:  458 ms
```
The performance depends on the chosen batch size. In particular, if the batch size becomes larger as the number of trajectories the performance will deteriorate.

[vanilla]: http://www.kr.tuwien.ac.at/staff/eiter/et-archive/cdtr9464.pdf
