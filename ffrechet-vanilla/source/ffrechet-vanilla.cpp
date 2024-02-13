#include <cassert>
#include <cmath>
#include <span>
#include <vector>

#include "ffrechet-vanilla/ffrechet-vanilla.hpp"

namespace
{
[[nodiscard]] float metric(float dx, float dy)
{
    return std::hypot(dx, dy);
}

[[nodiscard]] float frechet_distance(std::span<const float> px,
                                     std::span<const float> py,
                                     std::span<const float> qx,
                                     std::span<const float> qy)
{
    using std::max;
    using std::min;

    const auto P = px.size();
    assert(P == py.size());

    const auto Q = qx.size();
    assert(Q == qy.size());

    std::vector<float> d(P * Q);
    for (std::size_t i = 0; i < P; i++)
    {
        for (std::size_t j = 0; j < Q; j++)
        {
            d[i * Q + j] = metric(px[i] - qx[j], py[i] - qy[j]);
        }
    }

    for (std::size_t i = 1; i < P; i++)
    {
        d[i * Q] = max(d[(i - 1) * Q], d[i * Q]);
    }

    for (std::size_t j = 1; j < Q; j++)
    {
        d[j] = max(d[j - 1], d[j]);
    }

    for (std::size_t i = 1; i < P; i++)
    {
        for (std::size_t j = 1; j < Q; j++)
        {
            d[i * Q + j] = max(                                                         //
                min(min(d[(i - 1) * Q + j], d[(i - 1) * Q + j - 1]), d[i * Q + j - 1]), //
                d[i * Q + j]                                                            //
            );
        }
    }

    return d[P * Q - 1];
}
} // namespace

void vanilla_frechet_distance(const float* const* px,
                              const float* const* py,
                              const unsigned* P,
                              const unsigned N,
                              const float* qx,
                              const float* qy,
                              const unsigned Q,
                              float* d)
{
    for (std::size_t i = 0; i < N; i++)
    {
        d[i] = ::frechet_distance(
            std::span{px[i], P[i]}, std::span{py[i], P[i]}, std::span{qx, Q}, std::span{qy, Q});
    }
}
