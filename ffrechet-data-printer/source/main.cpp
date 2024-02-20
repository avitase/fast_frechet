#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <ffrechet-data/ffrechet-data.hpp>

int main(int argc, char** argv)
{
    if (argc == 2 and (std::strcmp(argv[1], "--help") == 0 or std::strcmp(argv[1], "-h") == 0))
    {
        std::cout << "Usage: " << argv[0] << " [P_max] [p (%)] [N] [seed]\n";
        return EXIT_SUCCESS;
    }

    const ::fast_frechet::data::BinomParams params{
        .k = (argc > 1) ? std::strtoull(argv[1], nullptr, 10) : 5U,
        .p = (argc > 2) ? std::strtod(argv[2], nullptr) / 100. : 1.};
    const auto N = (argc > 3) ? std::strtoull(argv[3], nullptr, 10) : 10U;
    const auto seed = (argc > 4) ? static_cast<unsigned>(std::strtoul(argv[4], nullptr, 10)) : 0U;

    const auto& trajectories = ::fast_frechet::data::generate_trajectories<float>(N, params, seed);

    std::cout << "{\n";
    std::cout << "    \"P_max\": " << params.k << ",\n";
    std::cout << "    \"p\": " << params.p << ",\n";
    std::cout << "    \"N\": " << N << ",\n";
    std::cout << "    \"seed\": " << seed << ",\n";
    std::cout << "    \"trajectories\": [\n";
    for (std::size_t i = 0; i < trajectories.size(); i++)
    {
        const auto& points = trajectories[i];
        assert(points.size() >= 2);

        if (i != 0)
        {
            std::cout << ",\n";
        }
        for (std::size_t j = 0; j < points.size(); j++)
        {
            std::cout << (j == 0 ? "        [" : ", ");
            std::cout << "[" << points.x[j] << ", " << points.y[j] << "]";
        }
        std::cout << "]";
    }
    std::cout << "\n    ]\n";
    std::cout << "}\n";

    return EXIT_SUCCESS;
}
