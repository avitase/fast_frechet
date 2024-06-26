# Fast Discrete Fréchet Distance 
[![arXiv](https://img.shields.io/badge/arXiv-2404.05708-b31b1b.svg)](https://arxiv.org/abs/2404.05708)

This is a collection of different C++ implementations for calculating the discrete [Fréchet distance](https://en.wikipedia.org/wiki/Fr%C3%A9chet_distance) between two polygonal curves:

1. [`vanilla`](ffrechet-vanilla/source/ffrechet-vanilla.cpp): A recursion-free adaptation of the original algorithm as proposed in [_Computing Discrete Fréchet Distance_ by T. Eiter and H. Mannila (1994)][vanilla], used as a baseline.
1. [`linear`](ffrechet-linear/source/ffrechet-linear.cpp): This formulation reduces the quadratic memory footprint to a linear one.
1. [`SIMD`](ffrechet-simd/source/ffrechet-simd.cpp): Formulation using SIMD parallelization on a single CPU core.
1. [`CUDA`](ffrechet-cuda/source/ffrechet-cuda.cu): Formulation using CUDA.

Implementations of all these variants can be found under `ffrechet-{vanilla,linear,simd,cuda}/source/` or by simply clicking on the listed names above.

## Toolchain Requirements ⚙️

This project has been primarily tested on Linux environments. Please note the following dependencies:

1. [SIMD implementation][ffrechet-simd_toolchain.cmake]: Requires at least GCC-11, as it relies on the experimental SIMD implementation of the [Parallelism Technical Specification (TS) v2][std::experimental::simd].
2. [CUDA implementation][ffrechet-cuda_toolchain.cmake]: Requires a compiler version compatible with the NVCC installation.

You can customize the compiler versions by editing the respective toolchain files [`ffrechet-simd/ffrechet-simd_toolchain.cmake`][ffrechet-simd_toolchain.cmake] and [`ffrechet-simd/ffrechet-cuda_toolchain.cmake`][ffrechet-cuda_toolchain.cmake].

## Installation 🛠️

First, make sure that you have checked out the dependencies ([google-benchmark][google-benchmark] and [google-test][google-test]) by running
```bash
$ git submodule init
$ git submodule update
```

Then, you can customize the build options in `CMakeUserPresets.json` or simply copy the default one from [`CMakeUserPresets.json.EXAMPLE`](CMakeUserPresets.json.EXAMPLE):
```bash
$ cp CMakeUserPresets.json.EXAMPLE CMakeUserPresets.json
```

Finally, configure and build the entire project via
```bash
$ cmake --preset=release
$ cmake --build --preset=release
```

If you want to run the benchmark, type:
```bash
$ ./build/release/install/bin/ffrechet-benchmark \
--benchmark_out_format=json \
--benchmark_out=benchmark.json
```
this will run the benchmark and store the results in `benchmark.json`.
Remember to enable the performance mode on your CPU before running the benchmark, e.g., via
```bash
$ sudo cpupower frequency-set --governor performance
```

Afterwards, you can reset the performance mode back to _powersave_ via 
```bash
$ sudo cpupower frequency-set --governor powersave
```

## Developer Mode 👷

In case you are interested in contributing to this project, you might find our `debug` preset helpful:
```bash
$ cmake --preset=debug
$ cmake --build --preset=debug
```

You can test your changes by running

```bash
$ ./build/debug/install/bin/ffrechet-test
```

Please make sure to obey the [formatting](.clang-format), for example by running
```bash
$ cmake --build --preset=debug -t format-check
$ cmake --build --preset=debug -t format-fix
```

## Benchmark results and other visualizations 🎨

We use Jupyter Notebooks to render the visualizations of the results of the benchmarks. You can find them [here][notebooks] alongside others.

## Python Implementations 🐍

Python implementations of the discrete Fréchet Distance can be found [here][fast_frechet-python].

[vanilla]: http://www.kr.tuwien.ac.at/staff/eiter/et-archive/cdtr9464.pdf
[std::experimental::simd]: https://en.cppreference.com/w/cpp/experimental/simd
[ffrechet-simd_toolchain.cmake]: ffrechet-simd/ffrechet-simd_toolchain.cmake 
[ffrechet-cuda_toolchain.cmake]: ffrechet-cuda/ffrechet-cuda_toolchain.cmake 
[google-benchmark]: https://github.com/google/benchmark
[google-test]: https://github.com/google/googletest
[notebooks]: https://avitase.github.io/fast_frechet/
[fast_frechet-python]: https://github.com/avitase/fast_frechet-python
