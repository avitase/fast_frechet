#pragma once

#include "ffrechet-linear/ffrechet-linear_export.hpp"

extern "C"
{
    FFRECHET_LINEAR_EXPORT void linear_frechet_distance(const float* const* px,
                                                        const float* const* py,
                                                        const unsigned* P,
                                                        unsigned N,
                                                        const float* qx,
                                                        const float* qy,
                                                        unsigned Q,
                                                        float* d);
}
