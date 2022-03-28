#pragma once

#include "VectorTrait.h"
#include "Tuple.h"
#include "MathUtil.h"

#include <iostream>

using namespace math;

class Color : public VectorTrait<Color>
{
private:
    std::array<float, 4> m_data{};
public:
    Color() = default;
    Color(float r, float g, float b): m_data{r,g,b, 0.f} {}
    
    // for the VectorTrait
    Color (float r, float g, float b ,float a) : m_data{r,g,b,a}{};

     bool operator==(const Color& t) const {
        return equal(R(), t.R())
            && equal(G(), t.G())
            && equal(B(), t.B());
    }

    Color(const Color& color) : m_data{color.m_data} {}
    const std::array<float, 4>& getData() const {return m_data;} 
    
    float R() const;
    float G() const; 
    float B() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& t);

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
    static const Color SHADOW;
};
