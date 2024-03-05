#include <cmath>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ffrechet-cwrapper/ffrechet-cwrapper.hpp>
#include <ffrechet-data/ffrechet-data.hpp>

namespace
{
TEST(FFrechetTest, Baseline)
{
    namespace data = ::fast_frechet::data;
    namespace baseline = ::fast_frechet::baseline;

    using ::testing::FloatEq;
    using ::testing::Pointwise;

    const auto N = 10U;
    const auto P = 100;
    const auto Q = 50U;

    const auto& p = data::generate_trajectories<float>(N, {P, 1.}, 42U);
    const auto q = data::generate_trajectories<float>(1U, {Q, 1.}, 43U).front();

    std::vector<float> expected(N, 0.f);
    for (std::size_t n = 0; n < N; n++)
    {
        for (std::size_t i = 0; i < P; i++)
        {
            for (std::size_t j = 0; j < Q; j++)
            {
                const auto dx = p[n].x[i] - q.x[j];
                const auto dy = p[n].y[i] - q.y[j];
                expected[n] += std::hypot(dx, dy);
            }
        }
    }

    EXPECT_THAT(baseline::frechet_distance(p, q), Pointwise(FloatEq(), expected));
}

TEST(FFrechetTest, SimpleTrajectories)
{
    namespace vanilla = ::fast_frechet::vanilla;
    namespace linear = ::fast_frechet::linear;
    namespace simd = ::fast_frechet::simd;
    namespace cuda = ::fast_frechet::cuda;

    using ::testing::FloatEq;
    using ::testing::Pointwise;
    using Trajectory = ::fast_frechet::data::Trajectory<float>;
    using Trajectories = std::vector<Trajectory>;

    const ::fast_frechet::cuda::KernelConfig cfg{.grid_size = 1, .block_size = 32};

    {
        const Trajectories p(1, {.x = {2.F}, .y = {3.F}});
        const Trajectory q{.x = {2.F}, .y = {3.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p(1, {.x = {2.F}, .y = {4.F}});
        const Trajectory q{.x = {2.F}, .y = {3.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p(1, {.x = {1.F}, .y = {3.F}});
        const Trajectory q{.x = {4.F}, .y = {3.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p{{.x = {0.F, 1.F}, .y = {0.F, 0.F}}};
        const Trajectory q{.x = {0.F, 1.F}, .y = {2.F, 1.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p{
            {.x = {0.F, -1.F}, .y = {0.F, -1.F}},
            {.x = {0.F, 0.F}, .y = {0.F, -1.F}},
        };
        const Trajectory q{.x = {0.F, -1.F}, .y = {0.F, -1.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p{
            {.x = {0.F, 1.F, 0.F}, .y = {0.F, 0.F, 1.F}},
            {.x = {0.F, 0.F}, .y = {0.F, 1.F}},
        };
        const Trajectory q{.x = {0.F, -1.F}, .y = {0.F, -1.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p{
            {.x = {1.F, 2.F}, .y = {0.F, 0.F}},
            {.x = {0.F, 0.F}, .y = {1.F, 0.F}},
        };
        const Trajectory q{.x = {1.F, 0.F}, .y = {0.F, 0.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }

    {
        const Trajectories p{
            {.x = {0.F, 1.F}, .y = {0.F, 0.F}},
            {.x = {0.F, 1.F, 2.F}, .y = {0.F, 0.F, 0.F}},
        };
        const Trajectory q{.x = {0.F}, .y = {0.F}};

        const auto& d = vanilla::frechet_distance(p, q);
        ASSERT_EQ(d.size(), p.size());

        EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
        EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
    }
}

TEST(FFrechetTest, ShortRandomTrajectories)
{
    namespace data = ::fast_frechet::data;
    namespace vanilla = ::fast_frechet::vanilla;
    namespace linear = ::fast_frechet::linear;
    namespace simd = ::fast_frechet::simd;
    namespace cuda = ::fast_frechet::cuda;

    using ::testing::FloatEq;
    using ::testing::Pointwise;

    const cuda::KernelConfig cfg{.grid_size = 1U, .block_size = 32U};

    const auto& p = data::generate_trajectories<float>(100U, {5, .9}, 42U);
    const auto q = data::generate_trajectories<float>(1U, {2, 1.}, 43U).front();

    const auto& d = vanilla::frechet_distance(p, q);
    ASSERT_EQ(d.size(), p.size());

    EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
    EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
    EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
}

TEST(FFrechetTest, LongRandomTrajectories)
{
    namespace data = ::fast_frechet::data;
    namespace vanilla = ::fast_frechet::vanilla;
    namespace linear = ::fast_frechet::linear;
    namespace simd = ::fast_frechet::simd;
    namespace cuda = ::fast_frechet::cuda;

    using ::testing::FloatEq;
    using ::testing::Pointwise;

    const cuda::KernelConfig cfg{.grid_size = 8U, .block_size = 32U};

    const auto& p = data::generate_trajectories<float>(100U, {100, .8}, 42U);
    const auto q = data::generate_trajectories<float>(1U, {80, 1.}, 43U).front();

    const auto& d = vanilla::frechet_distance(p, q);
    ASSERT_EQ(d.size(), p.size());

    EXPECT_THAT(linear::frechet_distance(p, q), Pointwise(FloatEq(), d));
    EXPECT_THAT(simd::frechet_distance(p, q), Pointwise(FloatEq(), d));
    EXPECT_THAT(cuda::frechet_distance(p, q, cfg), Pointwise(FloatEq(), d));
}
} // namespace
