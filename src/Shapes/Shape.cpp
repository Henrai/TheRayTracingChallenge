#include <Shapes/Shape.h>
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

Tuple Shape::NormalAt(const Tuple& point) const {
    Tuple objectPos = this->Transform().Inverse() * point;
    Tuple objectNormal = DoNormalAt(objectPos);
    Tuple worldNormal = this->Transform().Inverse().Transpose() * objectNormal;
    worldNormal[3] = 0.f;
    return worldNormal.normalize();
}