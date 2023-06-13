#include <Intersection.h>
#include <Ray.h>
#include <vector>
#include <stack>
#include <Shapes/Shape.h>
#include <iostream>

using namespace std;

void HitResult::toString() const {
    cout << "n1: " << n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "eyeV: " << eyev << endl;
    cout << "normalV: " << normalv << endl;
    cout << "under point: " << underPoint << endl;
}

double HitResult::schlick() const {
    double cos_i = eyev.Dot(normalv);
    if (n1 > n2) {
        double n = n1/n2;
        double sin2_t = n * n *(1 - cos_i * cos_i);
        if (sin2_t > 1.0) return 1.0;

        double cos_t = sqrt(1.0 - sin2_t);
        cos_i = cos_t;
    } 
    double r0 = (n1-n2)/((n1+n2)*(n1+n2));
    return r0  + (1-r0) * pow((1-cos_i),5);
}

bool Intersection::operator==(const Intersection& other) const {
    return   m_hitTime == other.m_hitTime && m_shape == other.m_shape;
}

bool Intersection::operator<(const Intersection& other) const {
    return m_hitTime < other.Distance();
}

Intersection Intersection::Hit(std::vector<Intersection>& xs)
{
   
    for (auto const& i : xs)
    {
        if (i.Distance() >= 0.f)
            return i;
    }
    return {nullptr, 0.f};
}

HitResult Intersection::getHitResult(const Intersection& intersection, const Ray& ray, std::vector<Intersection> xs) {

    if (intersection.Object() == nullptr) {
        HitResult res;
        res.shape = nullptr;
        return res;
    }

    double n1, n2;
    n1 = n2 = 1.0f;

    if (!xs.empty()) {
        std::stack<size_t> stack;
        int index = 0;
        while (index < xs.size()) {
            bool isHit =  xs[index] == intersection;
            if (isHit) {
                if (!stack.empty()) {
                    n1 = xs[stack.top()].Object()->getMaterial().refraction_index;
                }
            }
            if (!stack.empty() && xs[stack.top()].Object() == xs[index].Object()) {
                stack.pop();
            } else {
                stack.push(index);
            }
            if (isHit) {
                if(!stack.empty()) {
                    n2 = xs[stack.top()].Object()->getMaterial().refraction_index;
                }
            }
            index++;
        }  
    }
    
    Tuple hitPoint = ray.Position(intersection.Distance());
    Tuple normalV = intersection.Object()->NormalAt(hitPoint);
    bool isInside = normalV.Dot(-ray.Direction()) < 0;
    if(isInside) normalV = -normalV;
    Tuple reflectV = ray.Direction().Reflect(normalV);
    return {
        isInside,
        intersection.Distance(),// hit time
        n1,
        n2,
        intersection.Object(), //shape
        hitPoint,
        -ray.Direction(), // eyev
        normalV,  
        reflectV,
        hitPoint + normalV * SHADOW_OFFSET, // over point
        hitPoint - normalV * SHADOW_OFFSET  // under point
    };
}