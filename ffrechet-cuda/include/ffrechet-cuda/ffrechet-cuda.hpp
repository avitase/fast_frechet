#pragma once

#include "ffrechet-cuda/ffrechet-cuda_export.hpp"

struct FFRECHET_CUDA_EXPORT CUDAKernelConfig
{
    unsigned grid_size;
    unsigned block_size;
};

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
                                                    CUDAKernelConfig);
}
