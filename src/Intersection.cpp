#include <Intersection.h>
#include <Ray.h>
#include <vector>
#include <stack>
#include <Shapes/Shape.h>
#include <iostream>

using namespace std;

bool Intersection::operator==(const Intersection& other) const {
    return   m_hitTime == other.m_hitTime && m_shape == other.m_shape;
}

bool Intersection::operator<(const Intersection& other) const {
    return m_hitTime < other.Distance();
}

Intersection Intersection::Hit(std::vector<Intersection>& xs)
{
    sort(xs.begin(), xs.end());
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

    float n1, n2;
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
        intersection.Distance(),
        n1,
        n2,
        intersection.Object(),
        hitPoint,
        -ray.Direction(),
        normalV,
        reflectV,
        hitPoint + normalV * SHADOW_OFFSET,
        hitPoint - normalV * SHADOW_OFFSET
    };
}