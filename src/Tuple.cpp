#include "Tuple.h"
#include "MathUtil.h"
#include <cmath>
#include <iostream>

Tuple::Tuple(float x, float y, float z, float w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

Tuple::Tuple(const Tuple& t) {
    m_x = t.X();
    m_y = t.Y();
    m_z = t.Z();
    m_w = t.W();
}

Tuple::Tuple() {}

float Tuple::X() const {
    return m_x;
}
float Tuple::Y() const {
    return m_y;
}
float Tuple::Z() const {
    return m_z;
}
float Tuple::W() const {
    return m_w;
}

bool Tuple::IsPoint() const {
    return !IsVector();
}
bool Tuple::IsVector() const{
    return m_w == 0.0;
}

Tuple::~Tuple()
{
}

Tuple Tuple::operator+(const Tuple& t) const {
    return Tuple(m_x + t.X(), m_y+ t.Y(), m_z + t.Z(),m_w + t.W());
}

Tuple Tuple::operator-(const Tuple& t) const {
    return Tuple(m_x - t.X(), m_y- t.Y(), m_z - t.Z(),m_w - t.W());
}

bool Tuple::operator==(const Tuple& t) const {
    return equal(m_x, t.X())
        && equal(m_y, t.Y())
        && equal(m_z, t.Z())
        && equal(m_w, t.W());
}

Tuple Tuple::operator-() const {
    return Tuple(-m_x, -m_y, -m_z, -m_w);
}

Tuple Tuple::Point(float x, float y, float z) {
    return {x, y, z, 1.0};
}

Tuple Tuple::Vector(float x, float y, float z) {
    return {x, y, z, 0.0};
}

Tuple Tuple::operator*(float scalar) const {
    return {m_x * scalar, m_y * scalar , m_z * scalar, m_w * scalar};
}

Tuple Tuple::operator/(float scalar) const {
     return {m_x / scalar, m_y / scalar , m_z / scalar, m_w / scalar};
}

float Tuple::Dot(const Tuple& t) const {
    return m_x * t.X() + m_y * t.Y() + m_z * t.Z();
}

Tuple Tuple::Cross(const Tuple& t) const {
    return Vector (
        m_y * t.Z() - m_z * t.Y(),
        m_z * t.X() - m_x * t.Z(),
        m_x * t.Y() - m_y * t.X()
    );
}

float Tuple::Magnitude() const {
    return std::sqrt(this->Dot(*this));
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
    os << t.X() << ", " << t.Y() << ", " << t.Z() <<")";
    return os;
}

