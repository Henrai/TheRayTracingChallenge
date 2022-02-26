#ifndef __MATHUTIL_H__
#define __MATHUTIL_H__

#include <cmath>

#define EPSILON 0.00001
namespace math{
inline bool equal(float d1, float d2) {
    return  std::abs(d1 - d2) < EPSILON;
}
}

#endif