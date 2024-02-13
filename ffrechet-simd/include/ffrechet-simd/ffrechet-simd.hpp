#pragma once

#include "ffrechet-simd/ffrechet-simd_export.hpp"

extern "C"
{
    FFRECHET_SIMD_EXPORT void simd_frechet_distance(const float* const* px,
                                                    const float* const* py,
                                                    const unsigned* P,
                                                    unsigned N,
                                                    const float* qx,
                                                    const float* qy,
                                                    unsigned Q,
                                                    float* d);
}
