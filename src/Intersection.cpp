#include <Intersection.h>
#include <Ray.h>

#include <vector>

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

HitResult Intersection::getHitResult(const Intersection& intersection, const Ray& ray) {
    if (intersection.Object() == nullptr) {
        HitResult res;
        res.shape = nullptr;
        return res;
    }
    Tuple hitPoint = ray.Position(intersection.Distance());
    Tuple normalV = intersection.Object()->NormalAt(hitPoint);
    bool isInside = normalV.Dot(-ray.Direction()) < 0;
    if(isInside) normalV = -normalV;
    return {
        isInside,
        intersection.Distance(),
        intersection.Object(),
        hitPoint,
        -ray.Direction(),
        normalV,
        hitPoint + normalV * EPSILON
    };
}