#ifndef __MATHUTIL_H__
#define __MATHUTIL_H__

#include <cmath>

#define EPSILON 0.00001

inline bool equal(double d1, double d2) {
    return std::abs(d1 - d2) < EPSILON;
}

#endif