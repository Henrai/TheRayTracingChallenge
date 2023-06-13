#include <Camera.h>
#include <Transformation.h>
#include <Ray.h>
#include <Matrix.h>

#include <cmath>

#include <iostream>

using namespace std;

Camera::Camera(int h, int v, double fieldOfView): 
        m_hsize(h), m_vsize(v), m_fov(fieldOfView), m_transform(Matrix4::Identity()) {
    double halfView = std::tanf(m_fov/2);
    double aspect = static_cast<double>(m_hsize) / static_cast<double>(m_vsize);
    if (aspect >= 1) {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    } else {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }

    m_pixelSize = m_halfWidth * 2 / static_cast<double>(m_hsize);
}

void Camera::UpdateTransform(Tuple from, Tuple to, Tuple up) {
    m_transform = matrix::ViewTransformation(from, to, up);
}

Ray Camera::RayFromPixel(double px, double py) const {
     double x_offset = (px + 0.5) * m_pixelSize;
     double y_offset = (py + 0.5) * m_pixelSize;

     double world_x = m_halfWidth - x_offset;
     double world_y = m_halfHeight - y_offset;

     cout << m_transform << endl;

     Matrix4 inv_trans = m_transform.Inverse();

     cout << inv_trans << endl;

     cout << world_x << "  " << world_y << endl;

     Tuple pixel = inv_trans  * Tuple::Point(world_x, world_y, -1);
     Tuple origin = inv_trans * Tuple::Point(0.f ,0.f ,0.f);

     return Ray(origin, (pixel-origin).normalize());
 }
