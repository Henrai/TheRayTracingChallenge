#pragma once

#include "../Ray.h"
#include "Shape.h"
#include "../Intersection.h"
#include "../Transformation.h"
#include <vector>

class Tuple;

class Sphere : public Shape
{
private:
    void DoIntersect(const Ray& ray, std::vector<Intersection>& intersects) const override;
    Tuple DoNormalAt(const Tuple& point) const override;
    
public:
    Sphere(const std::string& name = "") : Shape(name) {}
    ~Sphere() {}
    
};
