#pragma once

#include "../Intersection.h"
#include "../Matrix.h"
#include "../Material.h"

#include <vector>

class Ray;
class Tuple;


class Shape : public std::enable_shared_from_this<Shape>
{
private:
Matrix4 m_transform;
Matrix4 m_invTransform;
Material m_material;

virtual void DoIntersect(const Ray& ray, std::vector<Intersection>& intersect) const = 0;

public:
    Shape() :m_transform(Matrix4::Identity()), m_invTransform(Matrix4::Identity()) {}

    void SetTransform(Matrix4 const& t);
    const Matrix4& Transform() const { return m_transform; }
    const Matrix4& InvTransform() const { return m_invTransform; }
    const Material& getMaterial() const { return m_material;}
    Material& getMaterial(){ return m_material;}
    
    void Intersect(const Ray& ray, std::vector<Intersection>& intersect) const;

    virtual Tuple NormalAt(Tuple point) const = 0;
    virtual ~Shape() {}
};

