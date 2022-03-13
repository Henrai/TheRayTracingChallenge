#pragma once

#include "Tuple.h"

class Color : public Tuple
{

public:
    Color() = default;
    Color(float r, float g, float b);
    Color(const Color& color);
    Color(const Tuple& color);
    float R() const;
    float G() const; 
    float B() const;

    Color HadamardProduct(const Color& c) const;

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
};
