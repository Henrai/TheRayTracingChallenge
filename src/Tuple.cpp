#include "Tuple.h"
#include "MathUtil.h"
#include <cmath>
#include <cassert>
#include <iostream>

using namespace math;

Tuple::Tuple(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Tuple::Tuple(const Tuple& t) {
    this->x = t.x;
    this->y = t.y;
    this->z = t.z;
    this->w = t.w;
}

bool Tuple::IsPoint() const {
    return !IsVector();
}
bool Tuple::IsVector() const{
    return this->w == 0.0;
}

Tuple::~Tuple()
{
}

Tuple Tuple::operator+(const Tuple& t) const {
    return Tuple(this->x + t.x, this->y+ t.y, this->z + t.z,this->w + t.w);
}

Tuple Tuple::operator-(const Tuple& t) const {
    return Tuple(this->x - t.x, this->y- t.y, this->z - t.z,this->w - t.w);
}

bool Tuple::operator==(const Tuple& t) const {
    return equal(this->x, t.x)
        && equal(this->y, t.y)
        && equal(this->z, t.z)
        && equal(this->w, t.w);
}

Tuple Tuple::operator-() const {
    return Tuple(-this->x, -this->y, -this->z, -this->w);
}

Tuple Tuple::Point(float x, float y, float z) {
    return {x, y, z, 1.0};
}

Tuple Tuple::Vector(float x, float y, float z) {
    return {x, y, z, 0.0};
}

Tuple Tuple::operator*(float scalar) const {
    return {this->x * scalar, this->y * scalar , this->z * scalar, this->w * scalar};
}

Tuple Tuple::operator*(const Tuple& t) const {
    return {this->x * t.x, this->y * t.y , this->z * t.z, this->w * t.w};
}

Tuple Tuple::operator/(float scalar) const {
     return {this->x / scalar, this->y / scalar , this->z / scalar, this->w / scalar};
}

float& Tuple::operator[](size_t index) {
    if (index == 0) {
        return this->x;
    } else if (index == 1) {
        return this->y;
    } else if (index == 2) {
        return this->z;
    } else {
        return this->w;
    }
}

const float Tuple::operator[](size_t index) const {
    if (index == 0) {
        return this->x;
    } else if (index == 1) {
        return this->y;
    } else if (index == 2) {
        return this->z;
    } else {
        return this->w;
    }
}


float Tuple::Dot(const Tuple& t) const {
    return this->x * t.x + this->y * t.y + this->z * t.z;
}

Tuple Tuple::Cross(const Tuple& t) const {
    return Vector (
        this->y * t.z - this->z * t.y,
        this->z * t.x - this->x * t.z,
        this->x * t.y - this->y * t.x
    );
}

float Tuple::Magnitude() const {
    return std::sqrtf(this->Dot(*this));
}

Tuple Tuple::normalize() const {
   return *this / Magnitude();
}

std::ostream& operator<<(std::ostream& os, const Tuple& t)
{
    if(t.IsPoint()) {
        os << "P(" ;
    } else {
        os << "V(";
    }
    os << t.x << ", " << t.y << ", " << t.z <<")";
    return os;
}


Tuple Tuple::Reflect(const Tuple normal) const {
    assert(IsVector() && normal.IsVector());
    return *this -  normal * 2 * this->Dot(normal);

}