#ifndef RUNNER_MATHS_HPP
#define RUNNER_MATHS_HPP

#include "GCE/Core/Maths/Vector3.h"

#define PI 3.1415926535f
#define DEG2RAD PI/180.0f
#define RAD2DEG 180.0f/PI

inline sr::Vector3 Lerp(sr::Vector3 const& from, sr::Vector3 const& to, float32 const t)
{
    return from + (to - from) * t;
}

#endif