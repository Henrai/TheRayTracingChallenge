#include <Tuple.h>
#include <Ray.h>
#include <Matrix.h>
#include <Transformation.h>

#include <gtest/gtest.h>

#include <iostream>
using namespace std;

TEST(RayTest, pointFromADistance){
    Ray r(Tuple::Point(2.f,3.f,4.f), Tuple::Vector(1.f,0.f,0.f));

    EXPECT_TRUE (r.Position(0.f) == Tuple::Point(2.f,3.f,4.f));
    EXPECT_TRUE (r.Position(1.f) == Tuple::Point(3.f,3.f,4.f));
    EXPECT_TRUE (r.Position(-1.f) == Tuple::Point(1.f,3.f,4.f));
    EXPECT_TRUE (r.Position(2.5f) == Tuple::Point(4.5f,3.f,4.f));
}

TEST(RayTest, Transformation) {
    Ray ray(Tuple::Point(1.f,2.f,3.f), Tuple::Vector(0.f, 1.f, 0));
    Matrix4 trans = matrix::Translation(3.f,4.f,5.f);

    Ray r2 = ray.Trasnsform(trans);

    EXPECT_TRUE(r2.Origin() == Tuple::Point(4.f, 6.f, 8.f));
    EXPECT_TRUE(r2.Direction() == Tuple::Vector(0.f, 1.f, 0.f));
}

TEST(RayTest, Scaling) {
    Ray ray(Tuple::Point(1.f,2.f,3.f), Tuple::Vector(0.f, 1.f, 0));
    Matrix4 trans = matrix::Scale(2.f,3.f,4.f);

    Ray r2 = ray.Trasnsform(trans);
    
    EXPECT_TRUE(r2.Origin() == Tuple::Point(2.f, 6.f, 12.f));
    EXPECT_TRUE(r2.Direction() == Tuple::Vector(0.f, 3.f, 0.f));
}