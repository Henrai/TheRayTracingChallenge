#ifndef __COLOR_H__
#define __COLOR_H__
#include "Tuple.h"

class Color : public Tuple
{

public:
    Color();
    Color(double r, double g, double b);
    Color(const Color& color);

    double R() const;
    double G() const; 
    double B() const;

    Color HadamardProduct(const Color& c) const;

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color BLACK;
    static const Color WHITE;
};
#endif