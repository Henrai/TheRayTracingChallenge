#pragma once

#include "../Intersection.h"
#include "../Matrix.h"
#include "../Material.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Ray;
class Tuple;


class Shape : public std::enable_shared_from_this<Shape>
{
private:
std::string m_name;
Matrix4 m_transform;
Matrix4 m_invTransform;
Material m_material;

virtual void DoIntersect(const Ray& ray, std::vector<Intersection>& intersect) const = 0;
virtual Tuple DoNormalAt(const Tuple& point) const = 0;

public:

    static std::shared_ptr<Shape> getShape(const std::string& name, const std::string& shapeType);
    
    Shape(const std::string& name = "") :m_transform(Matrix4::Identity()), m_invTransform(Matrix4::Identity()), m_name(name) {}

    void SetTransform(Matrix4 const& t);
    void SetMaterial(const Material& m); 

    const Matrix4& Transform() const { return m_transform; }
    const Matrix4& InvTransform() const { return m_invTransform; }
    const Material& getMaterial() const { return m_material;}
    Material& getMaterial(){ return m_material;}
    

    void Intersect(const Ray& ray, std::vector<Intersection>& intersect) const;
    Tuple NormalAt(const Tuple& point) const;

    void print() const {
        std::cout << "name: " << m_name << std::endl;
        m_material.print();
        std::cout << m_transform << std::endl;
        std::cout <<std::endl;
    }
    
    virtual ~Shape() {}
};

