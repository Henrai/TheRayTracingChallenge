#include <Shape.h>
#include <Matrix.h>
#include <Ray.h>

#include <vector>

void Shape::SetTransform(Matrix4 const& t) {
    m_transform = t;
    m_invTransform = t.Inverse();
}


void Shape::Intersect(const Ray& ray, std::vector<Intersection>& intersects) const {
    DoIntersect(ray.Trasnsform(this->InvTransform()), intersects);
}