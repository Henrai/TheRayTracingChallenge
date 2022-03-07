#include <Sphere.h>
#include <Intersection.h>

#include <cmath>
#include <vector>

void Sphere::Intersect(const Ray& ray, std::vector<Intersection>& Intersect) const {

    Tuple sphereToRay = ray.Origin() - Tuple::Point(0.f, 0.f , 0.f);

    float a = ray.Direction().Dot(ray.Direction());
    float b = 2 * ray.Direction().Dot(sphereToRay);
    float c = sphereToRay.Dot(sphereToRay) - 1.f;
    
    float delta = b*b - 4*a*c;
    
    if (delta < 0) {
        return;
    }
    
    Intersect.push_back(Intersection(shared_from_this(), (-1*b - sqrtf(delta))/(2*a)));
    Intersect.push_back(Intersection(shared_from_this(),  (-1*b + sqrtf(delta))/(2*a)));
}