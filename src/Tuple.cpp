#include "Tuple.h"
#include "MathUtil.h"
#include <cmath>
#include <cassert>
#include <iostream>

using namespace math;



bool Tuple::IsPoint() const {
    return !IsVector();
}
bool Tuple::IsVector() const{
    return (*this)[3] == 0.0f;
}



Tuple Tuple::Point(double x, double y, double z) {
    return {x, y, z, 1.0f};
}

Tuple Tuple::Vector(double x, double y, double z) {
    return {x, y, z, 0.0f};
}


std::ostream& operator<<(std::ostream& os, const Tuple& t)
{
    if(t.IsPoint()) {
        os << "P(" ;
    } else {
        os << "V(";
    }
    os << t[0] << ", " << t[1] << ", " << t[2] <<")";
    return os;
}


Tuple Tuple::Reflect(const Tuple normal) const {
    assert(IsVector() && normal.IsVector());
    return *this -  normal * 2.0f * this->Dot(normal);
}