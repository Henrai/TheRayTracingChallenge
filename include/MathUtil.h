#pragma once

#include <cmath>

namespace math{
#define EPSILON 0.00001f
inline bool equal(float d1, float d2) {
    return  std::abs(d1 - d2) < EPSILON;
}
}
