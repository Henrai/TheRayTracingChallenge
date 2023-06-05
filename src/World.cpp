#include <World.h>
#include <Intersection.h>
#include <Color.h>
#include <Light.h>
#include <Ray.h>

#include <vector>

#include<iostream>
using namespace std;

Color World::ShadeHit(const HitResult &hit, int remaining) const
{
    //cout << "okita shade hit" << endl;
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
    
    return result + reflectedColor(hit, remaining); //+ refracted_color(hit, remaining);
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

Color World::refracted_color(HitResult hitResult, int remaining) const {
    float n_ratio = hitResult.n1 / hitResult.n2;
    float cos_i = hitResult.eyev.Dot(hitResult.normalv);
    float sin2_t = n_ratio * n_ratio * (1 - cos_i*cos_i);
    if (remaining == 0 || sin2_t > 1 || hitResult.shape->getMaterial().transparency == 0) {
        //cout << remaining << " " << sin2_t << " " <<hitResult.shape->getMaterial().transparency<< endl;
        return Color(0, 0, 0);
    } else {
        //cout << "okita" << "!!" << endl;
        float cos_t = sqrt(1 - sin2_t);
        auto dir = hitResult.normalv * (n_ratio * cos_i - cos_t) - hitResult.eyev * n_ratio;
        auto refract_ray = Ray(hitResult.underPoint, dir);

        return ColorAt(refract_ray, remaining - 1) * hitResult.shape->getMaterial().transparency;
    }
}