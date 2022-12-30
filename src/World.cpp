#include <World.h>
#include <Intersection.h>
#include <Color.h>
#include <Light.h>
#include <Ray.h>

#include <vector>


Color World::ShadeHit(const HitResult &hit, int remaining) const
{
    Color result = Color::BLACK;
    if (hit.shape == nullptr)
    {
        return result;
    }
    for (auto i : m_lights)
    {
        result = result + lighting::PhongLinghting(
             hit.shape, 
             *i, // light
             hit.overPoint, 
             hit.eyev, 
             hit.normalv, 
             IsShadowed(hit.overPoint, i));
    }
    
    return result + reflectedColor(hit, remaining);
}

Color World::ColorAt(const Ray &ray, int remaining) const
{
    std::vector<Intersection> xs;
    this->Intersect(ray, xs);
    HitResult hit = Intersection::getHitResult(Intersection::Hit(xs), ray);
    return this->ShadeHit(hit, remaining);
}

bool World::IsShadowed(const Tuple &point, std::shared_ptr<const PointLight> light) const
{
    Tuple l = light->position - point;

    float distance = l.Magnitude();
    Tuple dir = l.normalize();
    
    Ray r(point, dir);
    std::vector<Intersection> xs;
    this->Intersect(r, xs);
    Intersection hit = Intersection::Hit(xs);
    if (hit.Object() != nullptr && hit.Distance() >= 0.00001 && hit.Distance() < distance)
    {
        return true;
    }
    return false; 
}

Color World::reflectedColor(HitResult hitResult, int remaining) const {
    if(hitResult.shape->getMaterial().reflective < EPSILON || remaining <= 0) {
        return Color::BLACK;
    }
    Ray reflectRay(hitResult.overPoint, hitResult.reflectv);
    Color color = ColorAt(reflectRay, remaining - 1);
    return color * hitResult.shape->getMaterial().reflective;
}
