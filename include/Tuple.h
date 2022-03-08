#pragma once

#include <ostream>
class Tuple
{
private:
    float m_x;
    float m_y;
    float m_z;
    float m_w;
public:
    Tuple(float x, float y, float z, float w);
    Tuple(const Tuple& t);
    Tuple();

    float X() const;
    float Y() const;
    float Z() const;
    float W() const;

    bool IsPoint() const;
    bool IsVector() const;
    
    Tuple operator+(const Tuple& t) const;
    Tuple operator-(const Tuple& t) const;
    bool operator==(const Tuple& t) const;
    Tuple operator*(float scalar) const;
    Tuple operator/(float scalar) const;

    Tuple operator-() const;

    float& operator[](size_t index);
    const float operator[](size_t index) const;

    float Dot(const Tuple& t) const;
    Tuple Cross(const Tuple& t) const;
    float Magnitude() const;
    Tuple normalize() const;
    Tuple Reflect(const Tuple normal) const;

    virtual ~Tuple();

    static Tuple Point(float x, float y, float z);
    static Tuple Vector(float x, float y, float z);

    friend std::ostream& operator<<(std::ostream& os, const Tuple& t);
};
