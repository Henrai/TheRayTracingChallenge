#include <Shape.h>
#include <Matrix.h>

void Shape::SetTransform(Matrix4 const& t) {
    m_transform = t;
    m_invTransform = t.Inverse();
}
