#include <Sphere.h>
#include <Shape.h>
#include <Matrix.h>
#include <Transformation.h>

#include <gtest/gtest.h>

TEST(ShapeTest, CreateTransformedShpere) {
    Sphere s;
    EXPECT_TRUE(s.Transform() == Matrix4::Identity());

    Matrix4 Trans = matrix::Translation(2.f, 3.f, 4.f);

    s.SetTransform(Trans);

    EXPECT_TRUE(s.Transform() == Trans);
}