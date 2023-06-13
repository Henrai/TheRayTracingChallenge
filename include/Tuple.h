#pragma once

#include "VectorTrait.h"
#include "MathUtil.h"

#include <ostream>
#include <array>


using namespace math;

class Tuple : public VectorTrait<Tuple>{
private:
    std::array<double, 4> m_data{};
public:
    Tuple(double x, double y, double z, double w) {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[3] = w;
    }

    Tuple(const Tuple& t) {
        m_data = t.m_data;
    }

    Tuple() = default;

     bool operator==(const Tuple& t) const {
        return equal(m_data[0], m_data[0])
            && equal(m_data[1], m_data[1])
            && equal(m_data[2], m_data[2])
            && equal(m_data[3], m_data[3]);
    }

    double& operator[](size_t index) {
        return m_data[index];
    }
    const double operator[](size_t index) const {
        return m_data[index];
    }

    const std::array<double, 4>& getData() const {return m_data;}    
    
    bool IsPoint() const;
    bool IsVector() const;
    
    Tuple Reflect(const Tuple normal) const;

    static Tuple Point(double x, double y, double z);
    static Tuple Vector(double x, double y, double z);

    friend std::ostream& operator<<(std::ostream& os, const Tuple& t);
};
