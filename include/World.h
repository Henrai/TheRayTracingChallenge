#pragma once 

#include "Shape.h"
#include "Light.h"

#include<vector>

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

    void Intersect(const Ray& ray, std::vector<Intersection>& intersects) {
        for(auto i : m_objects) {
            i->Intersect(ray, intersects);
        }
    } 
};


