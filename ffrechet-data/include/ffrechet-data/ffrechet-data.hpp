#pragma once

#include <cassert>
#include <random>
#include <vector>

namespace fast_frechet::data
{
template <typename T>
struct Trajectory
{
    std::vector<T> x;
    std::vector<T> y;

    [[nodiscard]] std::size_t size() const
    {
        assert(x.size() == y.size());
        return x.size();
    }
};

template <typename T, typename Generator>
[[nodiscard]] auto generate_trajectory(const std::size_t N, Generator& g)
{
    std::uniform_int_distribution<std::size_t> d(0, 7);
    std::vector<std::pair<T, T>> v{
        {1, 0},   //
        {1, 1},   //
        {0, 1},   //
        {-1, 1},  //
        {-1, 0},  //
        {-1, -1}, //
        {0, -1},  //
        {1, -1},  //
    };

    Trajectory<T> trajectory;
    trajectory.x.reserve(N);
    trajectory.y.reserve(N);

    T x = 0;
    T y = 0;
    for (std::size_t i = 0; i < N; i++)
    {
        auto [dx, dy] = v[d(g)];
        x += dx;
        y += dy;
        trajectory.x.push_back(x);
        trajectory.y.push_back(y);
    }

    return trajectory;
}

struct BinomParams
{
    std::size_t k;
    double p;
};

template <typename T>
struct TrajectoriesView
{
    std::vector<const T*> x;
    std::vector<const T*> y;
    std::vector<unsigned> n;

    explicit TrajectoriesView(const std::vector<Trajectory<T>>& trajectories)
    {
        x.reserve(trajectories.size());
        y.reserve(trajectories.size());
        n.reserve(trajectories.size());

        for (const auto& trj : trajectories)
        {
            n.push_back(static_cast<unsigned>(trj.x.size()));
            x.push_back(trj.x.data());
            y.push_back(trj.y.data());
        }
    }

    [[nodiscard]] unsigned size() const
    {
        return static_cast<unsigned>(x.size());
    }
};

template <typename T>
[[nodiscard]] inline auto generate_trajectories(std::size_t count,
                                                BinomParams params,
                                                unsigned seed)
{
    std::mt19937 g{seed};
    std::binomial_distribution<std::size_t> d{params.k, params.p};

    std::vector<Trajectory<T>> trajectories(count);
    std::generate_n(trajectories.begin(), count, [&g, &d]() {
        return generate_trajectory<T>(d(g), g);
    });

    return trajectories;
}
} // namespace fast_frechet::data
