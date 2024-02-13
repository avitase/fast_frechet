# Fast Discrete Fréchet Distance 

This is a collection of different C++ implementations for calculating the discrete [Fréchet distance](https://en.wikipedia.org/wiki/Fr%C3%A9chet_distance) between two polygonal curves:

1. [`vanilla`](ffrechet-vanilla/source/ffrechet-vanilla.cpp): The baseline implementation as proposed in [_Computing Discrete Fréchet Distance_ by T. Eiter and H. Mannila (1994)][vanilla]
1. [`linear`](ffrechet-linear/source/ffrechet-linear.cpp): This formulation reduces the quadratic memory footprint to a linear one.
1. [`SIMD`](ffrechet-simd/source/ffrechet-simd.cpp): Formulation using SIMD parallelization on a single CPU core.
1. [`CUDA`](ffrechet-cuda/source/ffrechet-cuda.cu): Formulation using CUDA.

Implementations of all these variants can be found under `ffrechet-{vanilla,linear,simd,cuda}/source/` or by simply clicking on the listed names above.

## Installation

```bash
# release build & run benchmark
$ cmake --preset=release
$ cmake --build --preset=release

$ sudo cpupower frequency-set --governor performance
$ ./build/release/install/bin/ffrechet-benchmark --benchmark_out_format=json --benchmark_out=benchmark.json
$ sudo cpupower frequency-set --governor powersave
```

```bash
# debug build & run unit tests
$ cmake --preset=debug
$ cmake --build --preset=debug
$ cmake --build --preset=debug -t format-fix
$ ./build/debug/install/bin/ffrechet-test
```

[vanilla]: http://www.kr.tuwien.ac.at/staff/eiter/et-archive/cdtr9464.pdf
