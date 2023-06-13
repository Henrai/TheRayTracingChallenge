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
    
    return result + reflectedColor(hit, remaining) +  refracted_color(hit, remaining);
}

Color World::ColorAt(const Ray &ray, int remaining) const
{
    std::vector<Intersection> xs;
    this->Intersect(ray, xs);
    HitResult hit = Intersection::getHitResult(Intersection::Hit(xs), ray, xs);
    return this->ShadeHit(hit, remaining);
}

bool World::IsShadowed(const Tuple &point, std::shared_ptr<const PointLight> light) const
{
    Tuple l = light->position - point;

    double distance = l.Magnitude();
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
    

    double n_ratio = hitResult.n1 / hitResult.n2;
    double cos_i = hitResult.eyev.Dot(hitResult.normalv);
    double sin2_t = n_ratio * n_ratio * (1 - cos_i*cos_i);
    if (remaining == 0 || sin2_t > 1.0 || hitResult.shape->getMaterial().transparency == 0) {
        return Color(0, 0, 0);
    } else {
        

        double cos_t = sqrt(1 - sin2_t);
        auto dir = hitResult.normalv * (n_ratio * cos_i - cos_t) - hitResult.eyev * n_ratio;
        auto refract_ray = Ray(hitResult.underPoint, dir);
        Color refract_color = ColorAt(refract_ray, remaining - 1) * hitResult.shape->getMaterial().transparency;
       //if (remaining == 5) { 
        // cout << "== remaining " << remaining << " ==\n";
        // hitResult.toString();
        // cout << "n_ratio: " << n_ratio << endl;
        // cout << "cos_i: " << cos_i << endl;
        // cout << "sin2_t: " << sin2_t << endl;
        // cout << "cos_t: " << cos_t << endl;
        // cout << "refract dir: " << dir << endl;
        // cout << "refract color: " << refract_color << endl;
        // cout << endl << endl;
       //}
        return refract_color;
    }
}