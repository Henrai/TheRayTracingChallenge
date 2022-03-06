#pragma once

#include "Intersection.h"
#include "Matrix.h"

#include <vector>

class Ray;

class Shape : public std::enable_shared_from_this<Shape>
{
private:
Matrix4 m_transform;
Matrix4 m_invTransform;

public:
    Shape() :m_transform(Matrix4::Identity()), m_invTransform(Matrix4::Identity()) {}

    void SetTransform(Matrix4 const& t);
    const Matrix4& Transform() const { return m_transform; }
    const Matrix4& InvTransform() const { return m_invTransform; }


    virtual void Intersect(const Ray& ray, std::vector<Intersection>& Intersect) const = 0;
    virtual ~Shape() {}
};

