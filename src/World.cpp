#include <World.h>
#include <Intersection.h>
#include <Color.h>
#include <Light.h>

#include <vector>

Color World::ShadeHit(const HitResult& hit) const {
    Color result = Color::BLACK;
    if (hit.shape == nullptr) {
        return result;
    }
    for (auto i : m_lights) {
        result = result + lighting::PhongLinghting(
            hit.shape->getMaterial(),
            *i,
            hit.point,
            hit.eyev,
            hit.normalv
        );
    }
    return result;
}


Color World::ColorAt(const Ray& ray) const {
   std::vector<Intersection> xs;
   this->Intersect(ray, xs);
   HitResult hit = Intersection::getHitResult(Intersection::Hit(xs), ray);
   return this->ShadeHit(hit);
}
