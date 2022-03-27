#include <Ray.h>
#include <Tuple.h>
#include <Matrix.h>
#include <Intersection.h>

Tuple Ray::Position(float t) const {
    return m_origin + m_direction * t;
}

Ray Ray::Trasnsform(const Matrix4& trans) const {
    Tuple newOrin = trans * m_origin;
    Tuple newDir = trans * m_direction;
    return {newOrin, newDir};
}
