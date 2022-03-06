#include <Ray.h>
#include <Tuple.h>
#include <Matrix.h>
#include <Intersection.h>

Tuple Ray::position(float t) {
    return m_origin + m_direction * t;
}

Ray Ray::Trasnsform(const Matrix4& trans) const {
    Tuple newOrin = trans * m_origin;
    Tuple newDir = trans * m_direction;
    return {newOrin, newDir};
}


void Ray::Intersect(std::shared_ptr<const Shape> shape, std::vector<Intersection>& intersects) {
    Ray ray = this->Trasnsform(shape->InvTransform());
    shape->Intersect(ray, intersects);
}
