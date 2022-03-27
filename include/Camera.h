#pragma once

#include <Matrix.h>

class Ray;

class Camera
{
private:
    int m_hsize;
    int m_vsize;
    float m_fov;
    float m_halfWidth;
    float m_halfHeight;
    float m_pixelSize;
    Matrix4 m_transform;
public:
    Camera(int h, int v, float fieldOfView);

    int getHorizontalSize() const {
        return m_hsize;
    }

    int getVerticalSize() const {
        return m_vsize;
    }

    float getFov() const {
        return m_fov;
    }

    float getPixelSize() const {
        return m_pixelSize;
    }

    Matrix4 getTransformation() const {
        return m_transform;
    }

    void UpdateTransform(Tuple from, Tuple to, Tuple up);
    Ray RayFromPixel(float px, float py) const;

};
