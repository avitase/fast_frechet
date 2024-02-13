#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <span>
#include <vector>

#include "ffrechet-linear/ffrechet-linear.hpp"

namespace
{
[[nodiscard]] float metric(float dx, float dy)
{
    return std::hypot(dx, dy);
}

[[nodiscard]] float frechet_distance(std::span<const float> px,
                                     std::span<const float> py,
                                     std::span<const float> qx,
                                     std::span<const float> qy,
                                     std::vector<float>& v)
{
    using std::max;
    using std::min;

    const auto P = px.size();
    assert(P == py.size());

    const auto Q = qx.size();
    assert(Q == qy.size());

    { // transform + inclusive scan
        float acc = 0.F;
        for (std::size_t j = 0; j < Q; j++)
        {
            acc = max(acc, metric(px[0] - qx[j], py[0] - qy[j]));
            v[j] = acc;
        }
    }

    for (std::size_t i = 1; i < P; i++)
    {
        std::adjacent_difference(v.begin(), v.end(), v.begin(), [](float x, float acc) {
            return min(x, acc);
        });
        v[0] = max(v[0], metric(px[i] - qx[0], py[i] - qy[0]));

        for (std::size_t j = 1; j < Q; j++)
        {
            v[j] = max(min(v[j - 1], v[j]), metric(px[i] - qx[j], py[i] - qy[j]));
        }
    }

    return v.back();
}
} // namespace

void linear_frechet_distance(const float* const* px,
                             const float* const* py,
                             const unsigned* P,
                             const unsigned N,
                             const float* qx,
                             const float* qy,
                             const unsigned Q,
                             float* d)
{
    std::vector<float> v(Q);

    for (std::size_t i = 0; i < N; i++)
    {
        d[i] = ::frechet_distance(
            std::span{px[i], P[i]}, std::span{py[i], P[i]}, std::span{qx, Q}, std::span{qy, Q}, v);
    }
}
