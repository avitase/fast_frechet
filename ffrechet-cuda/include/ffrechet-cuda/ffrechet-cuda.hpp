#pragma once

#include "ffrechet-cuda/ffrechet-cuda_export.hpp"

namespace fast_frechet
{
namespace cuda
{
struct FFRECHET_CUDA_EXPORT KernelConfig
{
    unsigned grid_size;
    unsigned block_size;
};
} // namespace cuda
} // namespace fast_frechet

extern "C"
{
    FFRECHET_CUDA_EXPORT void cuda_frechet_distance(const float* const* px,
                                                    const float* const* py,
                                                    const unsigned* P,
                                                    unsigned N,
                                                    const float* qx,
                                                    const float* qy,
                                                    unsigned Q,
                                                    float* d,
                                                    const ::fast_frechet::cuda::KernelConfig&);
}
