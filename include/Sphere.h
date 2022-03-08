#pragma once

#include "Ray.h"
#include "Shape.h"
#include "Intersection.h"
#include "Transformation.h"
#include <vector>

class Sphere : public Shape
{
public:

    ~Sphere() {}

    void Intersect(const Ray& ray, std::vector<Intersection>& Intersect) const override;
    Tuple NormalAt(Tuple point) const override;
};
