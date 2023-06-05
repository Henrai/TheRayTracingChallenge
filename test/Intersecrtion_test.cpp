#include "TestUtil.h"
#include "Transformation.h"
#include <Tuple.h>
#include <Ray.h>
#include <Intersection.h>
#include <Shapes/Sphere.h>
#include <Shapes/Plane.h>
#include <MathUtil.h>

#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <list>

using namespace std;

TEST(IntersectTest, Initialize) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    Intersection intersect(shape, 1.0f);

    EXPECT_FLOAT_EQ(1.0f, intersect.Distance());
    EXPECT_TRUE(shape == intersect.Object());
}

TEST (IntersectTest, IntersectWithSphere) {
    Ray r(Tuple::Point(0.f, 0.f, 5.f), Tuple::Vector(0.f, 0.f, 1.f));
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    std::vector<Intersection> intersects = {};

    shape->Intersect(r, intersects);

    EXPECT_EQ(intersects.size(), 2);
    EXPECT_FLOAT_EQ(intersects[0].Distance(), -6.f);
    EXPECT_FLOAT_EQ(intersects[1].Distance(), -4.f);
}

TEST (IntersectTest, FindHit) {
   
    std::vector<Intersection> intersects = {};
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();

    Intersection i1 (shape, 2.f);
    Intersection i2 (shape, -3.f);
    Intersection i3 (shape, -6.f);
    Intersection i4 (shape, 5.f);
    intersects.push_back(i1);
    intersects.push_back(i2);
    intersects.push_back(i3);
    intersects.push_back(i4);

    Intersection hit = Intersection::Hit(intersects);
   
    EXPECT_TRUE(hit == i1);
}

TEST (IntersectTest, IntersectWithScaledSphere) {
    Ray r(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->SetTransform(matrix::Scale(2.f,2.f,2.f));
    std::vector<Intersection> intersects = {};

    shape->Intersect(r, intersects);

    EXPECT_EQ(intersects.size(), 2);
    EXPECT_FLOAT_EQ(intersects[0].Distance(), 3.f);
    EXPECT_FLOAT_EQ(intersects[1].Distance(), 7.f);
}


TEST(IntersectTest, HitOutSide) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    Ray r(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    Intersection intersect(shape, 4.0f);

    HitResult res = Intersection::getHitResult(intersect, r);

    EXPECT_TRUE(!res.isInside);
}

TEST(IntersectTest, HitInSide) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    Ray r(Tuple::Point(0.f, 0.f, 0.f), Tuple::Vector(0.f, 0.f, 1.f));
    Intersection intersect(shape, 1.f);

    HitResult res = Intersection::getHitResult(intersect, r);

    EXPECT_TRUE(res.isInside);
    EXPECT_TRUE(res.eyev == Tuple::Vector(0.f, 0.f, -1.f));
    EXPECT_TRUE(res.point == Tuple::Point(0.f, 0.f, 0.f));
    EXPECT_TRUE(res.normalv == Tuple::Vector(0.f, 0.f, -1.f));
}

TEST(IntersectTest, HitOffset) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->SetTransform(matrix::Translation(0,0,1));

    Ray r(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    
    Intersection intersect(shape, 5.f);

    HitResult hit = Intersection::getHitResult(intersect, r);
    cout << hit.overPoint << endl << hit.point << endl;
    EXPECT_TRUE(hit.overPoint[2] < EPSILON/2);
    EXPECT_TRUE(hit.point[2] > hit.overPoint[2]);
}

TEST(IntersectTest, reflectionVector) {
    std::shared_ptr<Plane> shape = std::make_shared<Plane>();
    Ray r(Tuple::Point(0, 1, -1), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(shape, sqrt(2));
    HitResult hit = Intersection::getHitResult(i, r);
    cout << hit.reflectv << endl;
    EXPECT_TRUE(hit.reflectv == Tuple::Vector(0, sqrt(2)/2, sqrt(2)/2));
}

TEST(IntersectTest, determingRefraction) {
    std::shared_ptr<Shape> A = std::make_unique<Sphere>();
    A->SetTransform(matrix::Scale(2, 2, 2));
    A->getMaterial().refraction_index = 1.5;

    std::shared_ptr<Shape> B = std::make_unique<Sphere>();
    B->SetTransform(matrix::Translation(0, 0, -0.25));
    B->getMaterial().refraction_index = 2.0f;

    std::shared_ptr<Shape> C = std::make_unique<Sphere>();
    C->SetTransform(matrix::Translation(0, 0, 0.25));
    C->getMaterial().refraction_index = 2.5;

    std::vector<Intersection> xs = {};
    xs.push_back({A, 2});
    xs.push_back({B, 2.75});
    xs.push_back({C, 3.25});
    xs.push_back({B, 4.75});
    xs.push_back({C, 5.25});
    xs.push_back({A, 6});

    std::vector<std::pair<float, float>> result = {
        {1.0,1.5}, {1.5, 2.0}, {2.0, 2.5}, {2.5, 2.5}, {2.5, 1.5}, {1.5, 1.0}
    };
    Ray r(Tuple::Point(0, 0, -4), Tuple::Vector(0, 0, 1));

    for (int i = 0; i < result.size(); i++) {
        HitResult hit = Intersection::getHitResult(xs[0], r, xs);
        EXPECT_DOUBLE_EQ(result[0].first , hit.n1);
        EXPECT_DOUBLE_EQ(result[0].second, hit.n2);
    }
    
}

TEST(IntersectTesr, computeUnderPoint) {
   Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
   auto shape = shared_glass_sphere();
   shape->SetTransform(matrix::Translation(0, 0, 1));
   std::vector<Intersection> xs = {{shape, 5}};
   HitResult hit = Intersection::getHitResult(xs[0], r, xs);

   EXPECT_LT(SHADOW_OFFSET/2, hit.underPoint[2]);
   EXPECT_LT(hit.point[2], hit.underPoint[2]);
}