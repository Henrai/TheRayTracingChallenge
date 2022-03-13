#include <Intersection.h>

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