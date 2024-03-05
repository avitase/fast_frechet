#include <cassert>
#include <experimental/simd>
#include <numeric>
#include <span>
#include <vector>

#include "ffrechet-baseline/ffrechet-baseline.hpp"

#ifndef FFRECHET_SIMD_LANE_MULTIPLIER
#define FFRECHET_SIMD_LANE_MULTIPLIER 1
#endif

namespace stdx = std::experimental;

namespace
{
[[nodiscard]] auto metric(auto dx, auto dy)
{
    return stdx::hypot(dx, dy);
}

template <std::size_t N>
[[nodiscard]] stdx::fixed_size_simd<float, N> baseline(
    std::vector<stdx::fixed_size_simd<float, N>> px,
    std::vector<stdx::fixed_size_simd<float, N>> py,
    std::span<const float> qx,
    std::span<const float> qy)
{
    using float_v = stdx::fixed_size_simd<float, N>;

    const auto P = px.size();
    assert(P == py.size());

    const auto Q = qx.size();
    assert(Q == qy.size());

    float_v acc = 0.f;
    for (std::size_t i = 0; i < P; i++)
    {
        for (std::size_t j = 0; j < Q; j++)
        {
            acc += metric(px[i] - qx[j], py[i] - qy[j]);
        }
    }

    return acc;
}

template <typename T>
[[nodiscard]] T max_element(const T* v, std::size_t N)
{
    T max = v[0];
    for (std::size_t i = 1; i < N; i++)
    {
        max = std::max(max, v[i]);
    }

    return max;
}
} // namespace

void baseline_frechet_distance(const float* const* px,
                               const float* const* py,
                               const unsigned* P,
                               const unsigned N,
                               const float* qx,
                               const float* qy,
                               const unsigned Q,
                               float* d)
{
    using T = float;
    constexpr auto N_LANES =
        stdx::simd_size_v<T, stdx::simd_abi::native<T>> * FFRECHET_SIMD_LANE_MULTIPLIER;
    using simd_t = stdx::fixed_size_simd<T, N_LANES>;
    const auto P_MAX = ::max_element(P, N);

    std::vector<simd_t> px_v(P_MAX);
    std::vector<simd_t> py_v(P_MAX);

    for (std::size_t i = 0; i < N; i += N_LANES)
    {
        const auto n = ::max_element(P + i, std::min(N_LANES, N - i));
        px_v.resize(n);
        py_v.resize(n);

        constexpr auto alignment = stdx::memory_alignment_v<simd_t>;
        for (std::size_t j = 0; j < n; j++)
        {
            alignas(alignment) std::array<T, N_LANES> mx = {};
            alignas(alignment) std::array<T, N_LANES> my = {};
            for (std::size_t k = 0; k < N_LANES; k++)
            {
                const auto a = std::min(i + k, static_cast<std::size_t>(N) - 1U);
                const auto b = std::min(j, static_cast<std::size_t>(P[a]) - 1U);
                mx[k] = px[a][b];
                my[k] = py[a][b];
            }

            px_v[j] = simd_t(mx.data(), stdx::vector_aligned);
            py_v[j] = simd_t(my.data(), stdx::vector_aligned);
        }

        alignas(alignment) std::array<T, N_LANES> mv = {};
        ::baseline<N_LANES>(px_v, py_v, std::span{qx, Q}, std::span{qy, Q})
            .copy_to(mv.data(), stdx::vector_aligned);

        for (std::size_t j = i; j < std::min(i + N_LANES, static_cast<std::size_t>(N)); j++)
        {
            d[j] = mv[j - i];
        }
    }
}
