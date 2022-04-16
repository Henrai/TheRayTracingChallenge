#pragma once 
#include "../Color.h"
#include "../Matrix.h"

#include <memory>

class Tuple;
class Shape;

class Pattern {
    
public:
    Pattern(): transform(Matrix4::Identity()) {}

    virtual Color PatternAt(Tuple point) const = 0;
    Color PatternAtShape(std::shared_ptr<const Shape> shape,  Tuple worldPoint) const;
    
    Matrix4 transform;
};
