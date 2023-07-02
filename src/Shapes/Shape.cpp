#include "Shapes/Plane.h"
#include "Shapes/Sphere.h"
#include <Shapes/Shape.h>
#include <Matrix.h>
#include <Ray.h>

#include <memory>
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

std::shared_ptr<Shape> Shape::getShape(const std::string &name, const std::string &shapeType) {
    std::cout << name  << " " << shapeType << std::endl;
    if (shapeType == "plane") {
        return std::make_shared<Plane>(name);
    } else if (shapeType == "sphere") { 
        return std::make_shared<Sphere>(name);
    } 
    return nullptr;
}

void Shape::SetMaterial(const Material &m) {
    m_material = m;
}