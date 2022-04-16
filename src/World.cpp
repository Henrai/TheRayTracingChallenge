#include <World.h>
#include <Intersection.h>
#include <Color.h>
#include <Light.h>
#include <Ray.h>

#include <vector>

#include <iostream>
using namespace std;

Color World::ShadeHit(const HitResult &hit) const
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
    return result;
}

Color World::ColorAt(const Ray &ray) const
{
    std::vector<Intersection> xs;
    this->Intersect(ray, xs);
    HitResult hit = Intersection::getHitResult(Intersection::Hit(xs), ray);
    return this->ShadeHit(hit);
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
    //cout<<hit.Distance();
    if (hit.Object() != nullptr && hit.Distance() >= 0.00001 && hit.Distance() < distance)
    {
        return true;
    }
    return false; 
}
