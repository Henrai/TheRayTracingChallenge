#pragma once

#include "../Ray.h"
#include "Shape.h"
#include "../Intersection.h"
#include "../Transformation.h"
#include <vector>

class Tuple;

class Plane : public Shape
{
private:
    void DoIntersect(const Ray& ray, std::vector<Intersection>& intersects) const override;
    Tuple DoNormalAt(const Tuple& point) const override;
    
public:
    Plane(const std::string& name = "") : Shape(name){}
    ~Plane() {}
    
};
