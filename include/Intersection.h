#pragma once

#include "Tuple.h"

#include<memory>

#define SHADOW_OFFSET 0.001

class Shape;
class Ray;

struct HitResult {
    bool isInside;
    float hitTime;
    std::shared_ptr<const Shape> shape;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    Tuple overPoint;
};

class Intersection
{
private:
    std::shared_ptr<const Shape> m_shape;
    float m_hitTime;

public:
    Intersection(std::shared_ptr<const Shape> shape, float t) : m_shape(shape), m_hitTime(t) {}
    Intersection (const Intersection& intersect) : m_shape(intersect.m_shape), m_hitTime(intersect.m_hitTime) {}

    float Distance() const {return m_hitTime;} 
    std::shared_ptr<const Shape> Object() const {return m_shape;}

    bool operator==(const Intersection& other) const;
    bool operator<(const Intersection& other) const;

    static HitResult getHitResult(const Intersection& intersection, const Ray& ray);
    
    static Intersection Hit(std::vector<Intersection>& xs);
};

