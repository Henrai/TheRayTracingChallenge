#pragma once

#include <Matrix.h>
#include <iostream>

class Ray;

class Camera
{
private:
    int m_hsize;
    int m_vsize;
    double m_fov;
    double m_halfWidth;
    double m_halfHeight;
    double m_pixelSize;
    Matrix4 m_transform;
public:
    Camera(int h, int v, double fieldOfView);

    int getHorizontalSize() const {
        return m_hsize;
    }

    int getVerticalSize() const {
        return m_vsize;
    }

    double getFov() const {
        return m_fov;
    }

    double getPixelSize() const {
        return m_pixelSize;
    }

    Matrix4 getTransformation() const {
        return m_transform;
    }

    void UpdateTransform(Tuple from, Tuple to, Tuple up);
    Ray RayFromPixel(double px, double py) const;
    
    void print() const {
        std::cout << "-----------camera----------\n";
        std::cout<< "hsize: " << m_hsize << " vsize: " <<  m_vsize << std::endl;
        std::cout << "fov: " << m_fov << std::endl;
    }

};
