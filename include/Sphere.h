#pragma once

#include "Ray.h"
#include "Shape.h"
#include "Intersection.h"
#include "Transformation.h"
#include <vector>

class Sphere : public Shape
{
private:
    void DoIntersect(const Ray& ray, std::vector<Intersection>& intersects) const override;

public:
    ~Sphere() {}
    Tuple NormalAt(Tuple point) const override;
};
