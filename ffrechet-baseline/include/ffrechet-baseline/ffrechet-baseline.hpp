#pragma once

#include "ffrechet-baseline/ffrechet-baseline_export.hpp"

extern "C"
{
    FFRECHET_BASELINE_EXPORT void baseline_frechet_distance(const float* const* px,
                                                            const float* const* py,
                                                            const unsigned* P,
                                                            unsigned N,
                                                            const float* qx,
                                                            const float* qy,
                                                            unsigned Q,
                                                            float* d);
}
