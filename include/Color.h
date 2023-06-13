#pragma once

#include "VectorTrait.h"
#include "Tuple.h"
#include "MathUtil.h"

#include <iostream>

using namespace math;

class Color : public VectorTrait<Color>
{
private:
    std::array<double, 4> m_data{};
public:
    Color() = default;
    Color(double r, double g, double b): m_data{r,g,b, 0.f} {}
    
    // for the VectorTrait
    Color (double r, double g, double b ,double a) : m_data{r,g,b,a}{};

     bool operator==(const Color& t) const {
        return equal(R(), t.R())
            && equal(G(), t.G())
            && equal(B(), t.B());
    }

    Color(const Color& color) : m_data{color.m_data} {}
    const std::array<double, 4>& getData() const {return m_data;} 
    
    double R() const;
    double G() const; 
    double B() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& t);

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
    static const Color SHADOW;
};
