#pragma once

#include <MathUtil.h>
#include <cmath>

using namespace math;

/***
 * Both the Color and Tuple share the same vector operation
 * abstaract the Vector trait to get rid of duplicate code.
 */
template <class T>
class VectorTrait
{
private:
    const T& impl() const {
        return static_cast<const T&>(*this);
    }
public:
    T operator+(const T& t) const {
        return T(
            impl().getData()[0] + t.getData()[0], 
            impl().getData()[1] + t.getData()[1], 
            impl().getData()[2] + t.getData()[2], 
            impl().getData()[3] + t.getData()[3]);
    }

    T operator-(const T& t) const {
        return T(
            impl().getData()[0] - t.getData()[0], 
            impl().getData()[1] - t.getData()[1], 
            impl().getData()[2] - t.getData()[2], 
            impl().getData()[3] - t.getData()[3]);        
    }

    T operator*(double scalar) const {
        return T(
            impl().getData()[0] * scalar, 
            impl().getData()[1] * scalar, 
            impl().getData()[2] * scalar, 
            impl().getData()[3] * scalar);
    }

    T operator*(const T& t) const {
         return T(
            impl().getData()[0] * t.getData()[0], 
            impl().getData()[1] * t.getData()[1], 
            impl().getData()[2] * t.getData()[2], 
            impl().getData()[3] * t.getData()[3]);
    }

    T operator/(double scalar) const {
         return T(
            impl().getData()[0] / scalar, 
            impl().getData()[1] / scalar, 
            impl().getData()[2] / scalar, 
            impl().getData()[3] / scalar);
    }

    T operator-() const {
        return T(
            -impl().getData()[0],
            -impl().getData()[1],
            -impl().getData()[2],
            -impl().getData()[3]
        );
    }


    double Dot(const T& t) const {
        return
            impl().getData()[0] * t.getData()[0]
          + impl().getData()[1] * t.getData()[1]
          + impl().getData()[2] * t.getData()[2]
          + impl().getData()[3] * t.getData()[3];
    }
    T Cross(const T& t) const {
        return T(
            impl().getData()[1] * t.getData()[2] - impl().getData()[2] * t.getData()[1],
            impl().getData()[2] * t.getData()[0] - impl().getData()[0] * t.getData()[2],
            impl().getData()[0] * t.getData()[1] - impl().getData()[1] * t.getData()[0],
            0.f
        );
    }

    double Magnitude() const {
        return std::sqrtf(this->Dot(impl()));
    }
    T normalize() const {
        return impl() / Magnitude();
    }
};


