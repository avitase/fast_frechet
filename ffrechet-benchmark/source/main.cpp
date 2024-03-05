#include <benchmark/benchmark.h>
#include <utility>
#include <vector>

#include <ffrechet-cwrapper/ffrechet-cwrapper.hpp>
#include <ffrechet-data/ffrechet-data.hpp>

namespace
{
[[nodiscard]] auto generate_trajectories(const benchmark::State& state)
{
    using ::fast_frechet::data::BinomParams;
    using ::fast_frechet::data::generate_trajectories;

    const auto seed = 0U;
    const auto N = static_cast<std::size_t>(state.range(0));

    const BinomParams params_p{
        .k = static_cast<std::size_t>(state.range(1)),
        .p = static_cast<double>(state.range(2)) / 100.,
    };

    const BinomParams params_q{
        .k = static_cast<std::size_t>(state.range(1) * state.range(2)) / 100,
        .p = 1.,
    };

    return std::make_tuple(generate_trajectories<float>(N, params_p, seed),
                           generate_trajectories<float>(1U, params_q, seed + 1).front());
}

[[nodiscard]] auto get_kernel_config(const benchmark::State& state)
{
    return ::fast_frechet::cuda::KernelConfig{
        .grid_size = static_cast<unsigned>(state.range(3)),
        .block_size = static_cast<unsigned>(state.range(4)),
    };
}
} // namespace

static void baseline(benchmark::State& state)
{
    const auto& [p, q] = ::generate_trajectories(state);

    // warm-up
    benchmark::DoNotOptimize(::fast_frechet::vanilla::frechet_distance(p, q));

    for (auto _ : state) // NOLINT
    {
        benchmark::DoNotOptimize(::fast_frechet::vanilla::frechet_distance(p, q));
        benchmark::ClobberMemory();
    }
}

static void ffrechet_vanilla(benchmark::State& state)
{
    const auto& [p, q] = ::generate_trajectories(state);

    // warm-up
    benchmark::DoNotOptimize(::fast_frechet::vanilla::frechet_distance(p, q));

    for (auto _ : state) // NOLINT
    {
        benchmark::DoNotOptimize(::fast_frechet::vanilla::frechet_distance(p, q));
        benchmark::ClobberMemory();
    }
}

static void ffrechet_linear(benchmark::State& state)
{
    const auto& [p, q] = ::generate_trajectories(state);

    // warm-up
    benchmark::DoNotOptimize(::fast_frechet::linear::frechet_distance(p, q));

    for (auto _ : state) // NOLINT
    {
        benchmark::DoNotOptimize(::fast_frechet::linear::frechet_distance(p, q));
        benchmark::ClobberMemory();
    }
}

static void ffrechet_simd(benchmark::State& state)
{
    const auto& [p, q] = ::generate_trajectories(state);

    // warm-up
    benchmark::DoNotOptimize(::fast_frechet::simd::frechet_distance(p, q));

    for (auto _ : state) // NOLINT
    {
        benchmark::DoNotOptimize(::fast_frechet::simd::frechet_distance(p, q));
        benchmark::ClobberMemory();
    }
}

static void ffrechet_cuda(benchmark::State& state)
{
    const auto& [p, q] = ::generate_trajectories(state);
    const auto cfg = get_kernel_config(state);

    // warm-up
    benchmark::DoNotOptimize(::fast_frechet::cuda::frechet_distance(p, q, cfg));

    for (auto _ : state) // NOLINT
    {
        benchmark::DoNotOptimize(::fast_frechet::cuda::frechet_distance(p, q, cfg));
        benchmark::ClobberMemory();
    }
}

BENCHMARK(ffrechet_cuda)
    ->Name("kernel_size")
    ->ArgsProduct({
        {1U << 13U},
        {1U << 10U},
        {100},
        ::benchmark::CreateRange(8, 256, 2),
        ::benchmark::CreateRange(32, 256, 2),
    });

BENCHMARK(ffrechet_vanilla)
    ->Name("vanilla-P")
    ->ArgsProduct({
        {1U << 10U},
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {100},
    });

BENCHMARK(ffrechet_linear)
    ->Name("linear-P")
    ->ArgsProduct({
        {1U << 10U},
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {100},
    });

BENCHMARK(ffrechet_simd)
    ->Name("simd-P")
    ->ArgsProduct({
        {1U << 10U},
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {100},
    });

BENCHMARK(ffrechet_cuda)
    ->Name("cuda-P")
    ->ArgsProduct({
        {1U << 10U},
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {100},
        {128},
        {64},
    });

BENCHMARK(ffrechet_vanilla)
    ->Name("vanilla-N")
    ->ArgsProduct({
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {1U << 10U},
        {100},
    });

BENCHMARK(ffrechet_linear)
    ->Name("linear-N")
    ->ArgsProduct({
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {1U << 10U},
        {100},
    });

BENCHMARK(ffrechet_simd)
    ->Name("simd-N")
    ->ArgsProduct({
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {1U << 10U},
        {100},
    });

BENCHMARK(ffrechet_cuda)
    ->Name("cuda-N")
    ->ArgsProduct({
        ::benchmark::CreateRange(1U << 5U, 1U << 14U, 2),
        {1U << 10U},
        {100},
        {128},
        {64},
    });

BENCHMARK_MAIN();
