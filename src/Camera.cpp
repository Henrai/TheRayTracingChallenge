#include <Camera.h>
#include <Transformation.h>
#include <Ray.h>
#include <Matrix.h>

#include <cmath>

#include <iostream>

using namespace std;

Camera::Camera(int h, int v, float fieldOfView): 
        m_hsize(h), m_vsize(v), m_fov(fieldOfView), m_transform(Matrix4::Identity()) {
    float halfView = std::tanf(m_fov/2);
    float aspect = static_cast<float>(m_hsize) / static_cast<float>(m_vsize);
    if (aspect >= 1) {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    } else {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }

    m_pixelSize = m_halfWidth * 2 / static_cast<float>(m_hsize);
}

void Camera::UpdateTransform(Tuple from, Tuple to, Tuple up) {
    m_transform = matrix::ViewTransformation(from, to, up);
}

Ray Camera::RayFromPixel(float px, float py) const {
     float x_offset = (px + 0.5) * m_pixelSize;
     float y_offset = (py + 0.5) * m_pixelSize;

     float world_x = m_halfWidth - x_offset;
     float world_y = m_halfHeight - y_offset;

     Matrix4 inv_trans = m_transform.Inverse();
     Tuple pixel = inv_trans  * Tuple::Point(world_x, world_y, -1);
     Tuple origin = inv_trans * Tuple::Point(0.f ,0.f ,0.f);

     return Ray(origin, (pixel-origin).normalize());
 }
