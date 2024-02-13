#pragma once

#include <cassert>
#include <vector>

#include <ffrechet-cuda/ffrechet-cuda.hpp>
#include <ffrechet-data/ffrechet-data.hpp>
#include <ffrechet-linear/ffrechet-linear.hpp>
#include <ffrechet-simd/ffrechet-simd.hpp>
#include <ffrechet-vanilla/ffrechet-vanilla.hpp>

namespace fast_frechet::vanilla
{
template <typename T>
[[nodiscard]] std::vector<T> frechet_distance(
    const std::vector<::fast_frechet::data::Trajectory<T>>& p,
    const ::fast_frechet::data::Trajectory<T>& q)
{
    const ::fast_frechet::data::TrajectoriesView view{p};

    const unsigned N = static_cast<unsigned>(view.n.size());
    assert(view.x.size() == N);
    assert(view.y.size() == N);

    const unsigned Q = static_cast<unsigned>(q.x.size());
    assert(q.y.size() == Q);

    std::vector<T> distance(view.size());
    vanilla_frechet_distance(
        view.x.data(), view.y.data(), view.n.data(), N, q.x.data(), q.y.data(), Q, distance.data());

    return distance;
}
} // namespace fast_frechet::vanilla

namespace fast_frechet::linear
{
template <typename T>
[[nodiscard]] std::vector<T> frechet_distance(
    const std::vector<::fast_frechet::data::Trajectory<T>>& p,
    const ::fast_frechet::data::Trajectory<T>& q)
{
    const ::fast_frechet::data::TrajectoriesView view{p};

    const unsigned N = static_cast<unsigned>(view.n.size());
    assert(view.x.size() == N);
    assert(view.y.size() == N);

    const unsigned Q = static_cast<unsigned>(q.x.size());
    assert(q.y.size() == Q);

    std::vector<T> distance(view.size());
    linear_frechet_distance(
        view.x.data(), view.y.data(), view.n.data(), N, q.x.data(), q.y.data(), Q, distance.data());

    return distance;
}
} // namespace fast_frechet::linear

namespace fast_frechet::simd
{
template <typename T>
[[nodiscard]] std::vector<T> frechet_distance(
    const std::vector<::fast_frechet::data::Trajectory<T>>& p,
    const ::fast_frechet::data::Trajectory<T>& q)
{
    const ::fast_frechet::data::TrajectoriesView view{p};

    const unsigned N = static_cast<unsigned>(view.n.size());
    assert(view.x.size() == N);
    assert(view.y.size() == N);

    const unsigned Q = static_cast<unsigned>(q.x.size());
    assert(q.y.size() == Q);

    std::vector<T> distance(view.size());
    simd_frechet_distance(
        view.x.data(), view.y.data(), view.n.data(), N, q.x.data(), q.y.data(), Q, distance.data());

    return distance;
}
} // namespace fast_frechet::simd

namespace fast_frechet::cuda
{
template <typename T>
[[nodiscard]] std::vector<T> frechet_distance(
    const std::vector<::fast_frechet::data::Trajectory<T>>& p,
    const ::fast_frechet::data::Trajectory<T>& q,
    const ::fast_frechet::cuda::KernelConfig& cfg)
{
    const ::fast_frechet::data::TrajectoriesView view{p};

    const unsigned N = static_cast<unsigned>(view.n.size());
    assert(view.x.size() == N);
    assert(view.y.size() == N);

    const unsigned Q = static_cast<unsigned>(q.x.size());
    assert(q.y.size() == Q);

    std::vector<T> distance(view.size());
    cuda_frechet_distance(view.x.data(),
                          view.y.data(),
                          view.n.data(),
                          N,
                          q.x.data(),
                          q.y.data(),
                          Q,
                          distance.data(),
                          cfg);

    return distance;
}
} // namespace fast_frechet::cuda
