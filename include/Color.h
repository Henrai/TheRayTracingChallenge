#ifndef __COLOR_H__
#define __COLOR_H__
#include "Tuple.h"

class Color : public Tuple
{

public:
    Color();
    Color(double r, double g, double b);
    Color(const Color& color);

    double Red() const;
    double Green() const; 
    double Blue() const;

    Color HadamardProduct(const Color& c) const;


};
#endif