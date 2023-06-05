#pragma once

#include "Tuple.h"

#include<memory>
#include<vector>

#define SHADOW_OFFSET 0.001

class Shape;
class Ray;
class Color; 

struct HitResult {
    bool isInside;
    float hitTime;
    float n1;
    float n2;
    std::shared_ptr<const Shape> shape;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    Tuple reflectv;
    Tuple overPoint;
    Tuple underPoint;
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

    static HitResult getHitResult(const Intersection& intersection, const Ray& ray, std::vector<Intersection> xs = {});
    static Intersection Hit(std::vector<Intersection>& xs);
};

