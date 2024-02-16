#include <stdexcept>
#include <string>

#include "ffrechet-cuda/ffrechet-cuda.hpp"

namespace fast_frechet
{
namespace cuda
{
void cuda_check(cudaError_t code)
{
    if (code != cudaSuccess)
    {
        throw std::runtime_error{"CUDA error: " + std::string{cudaGetErrorString(code)}};
    }
}

void cuda_check()
{
    cuda_check(cudaGetLastError());
}
} // namespace cuda
} // namespace fast_frechet
