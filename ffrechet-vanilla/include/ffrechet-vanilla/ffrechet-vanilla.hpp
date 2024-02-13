#pragma once

#include "ffrechet-vanilla/ffrechet-vanilla_export.hpp"

extern "C"
{
    FFRECHET_VANILLA_EXPORT void vanilla_frechet_distance(const float* const* px,
                                                          const float* const* py,
                                                          const unsigned* P,
                                                          unsigned N,
                                                          const float* qx,
                                                          const float* qy,
                                                          unsigned Q,
                                                          float* d);
}
