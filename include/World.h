#pragma once 

#include "Shapes/Shape.h"
#include "Light.h"

#include<vector>

struct HitResult;
class Color;

class World
{
private:
    std::vector<std::shared_ptr<const Shape> >  m_objects;
    std::vector<std::shared_ptr<const PointLight> > m_lights;

public:
    void AddShape(std::shared_ptr<const Shape> shape) {
        m_objects.push_back(shape);
    }
    void AddLight(std::shared_ptr<const PointLight> light) {
        m_lights.push_back(light);
    }

    const std::vector<std::shared_ptr<const Shape> >& getObjects() const{
        return m_objects;
    }

    const std::vector<std::shared_ptr<const PointLight> > getLights() const {
        return m_lights;
    }   

    void clearLight() {
        m_lights.clear();
    } 

    void clearObject() {
        m_objects.clear();
    }

    void Intersect(const Ray& ray, std::vector<Intersection>& intersects) const {
        for(auto i : m_objects) {
            i->Intersect(ray, intersects);
        }
    } 

    Color ShadeHit(const HitResult& hit, int remaining = 5) const;
    Color ColorAt(const Ray& ray, int remaining = 5) const;
    Color reflectedColor(HitResult hitResult, int remaining = 5) const;
    bool IsShadowed(const Tuple& point, std::shared_ptr<const PointLight> light) const;
};
