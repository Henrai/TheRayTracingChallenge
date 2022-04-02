#include <Shapes/Sphere.h>
#include <Shapes/Shape.h>
#include <Matrix.h>
#include <Transformation.h>

#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;

TEST(ShapeTest, CreateTransformedShpere) {
    Sphere s;
    EXPECT_TRUE(s.Transform() == Matrix4::Identity());

    Matrix4 Trans = matrix::Translation(2.f, 3.f, 4.f);

    s.SetTransform(Trans);

    EXPECT_TRUE(s.Transform() == Trans);
}

TEST(ShapeTest, NormalOfUnit) {
    Sphere s;
    Tuple n = s.NormalAt(Tuple::Point(1.f, 0.f, 0.f));

    EXPECT_TRUE(n == Tuple::Vector(1.f, 0.f, 0.f));

    Tuple n1 = s.NormalAt(Tuple::Point(sqrt(3.f)/3.f, sqrt(3.f)/3.f, sqrt(3.f)/3.f));
    EXPECT_TRUE(n1== Tuple::Vector(sqrt(3.f)/3.f, sqrt(3.f)/3.f, sqrt(3.f)/3.f));
}


TEST(ShapeTest, NormalOfTransformedSphere) {
    Sphere s;
    Matrix4 Trans = matrix::Translation(0.f, 1.f, 0.f);
    s.SetTransform(Trans);
    Tuple n = s.NormalAt(Tuple::Point(0.f, 1.70711f, -0.70711f));

    EXPECT_TRUE(n == Tuple::Vector(0.f, 0.70711f, -0.70711f));
}

TEST(ShapeTest, NormalOfScaledSphere) {
    Sphere s;
    Matrix4 Trans = matrix::Scale(1.f, 0.5f, 1.f) * matrix::RotationZ(M_PI/5);
    s.SetTransform(Trans);
    Tuple n = s.NormalAt(Tuple::Point(0.f, sqrt(2.f)/2.f, -sqrt(2.f)/2.f));
    cout << n << endl;
    EXPECT_TRUE(n == Tuple::Vector(0.f, 0.97014, -0.24254));
}
