#pragma once

#include "Tuple.h"
#include "Matrix.h"
#include "Shape.h"

#include <vector>

class Ray {
private:
    Tuple m_origin;
    Tuple m_direction;
public:
    Ray(const Tuple& origin, const Tuple& direction) : m_origin(origin), m_direction(direction) {}
    Tuple position(float t);
    Tuple Origin() const { return m_origin; }
    Tuple Direction() const { return m_direction; }

    Ray Trasnsform(const Matrix4& trans) const;
    void Intersect(std::shared_ptr<const Shape> shape, std::vector<Intersection>& intersects);
};