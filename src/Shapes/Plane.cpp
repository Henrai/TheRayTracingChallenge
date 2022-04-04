#include <Shapes/Plane.h>
#include <Intersection.h>
#include <Tuple.h>
#include <Ray.h>

#include <cmath>
#include <vector>

void Plane::DoIntersect(const Ray& ray, std::vector<Intersection>& intersect) const {

   if(fabs(ray.Direction()[1]) < EPSILON) return;

   intersect.push_back(Intersection(shared_from_this(), -ray.Origin()[1]/ ray.Direction()[1]));
}

Tuple  Plane::DoNormalAt(const Tuple& point) const {
    return Tuple::Vector(0, 1, 0);
}