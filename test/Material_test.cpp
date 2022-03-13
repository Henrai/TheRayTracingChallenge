#include <Material.h>
#include <Color.h>
#include <Light.h>
#include <Tuple.h>

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

using namespace std;

TEST(MaterialTest, DefaultMaterial) {
    Material m;
    EXPECT_TRUE(m.color == Color::WHITE);
    EXPECT_FLOAT_EQ(m.ambient, 0.1f);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9f);
    EXPECT_FLOAT_EQ(m.specular, 0.9f);
    EXPECT_FLOAT_EQ(m.shininess, 200.0f);
}

TEST(MaterialTest, EyeBetweenLS) {
    Material m;
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(m, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.9f, 1.9f, 1.9f));
}


TEST(MaterialTest, EyeBetweenLSWithEOffset) {
    Material m;
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, sqrt(2.f)/2.f, -sqrt(2.f)/2.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(m, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.f, 1.f, 1.f));
}

TEST(MaterialTest, EyeBetweenLSWithLOffset) {
    Material m;
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 10.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(m, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(.7364f, .7364f, .7364f));
}


TEST(MaterialTest, EyeBetweenLSWithLEReflect) {
    Material m;
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, -sqrt(2.f)/2.f, -sqrt(2.f)/2.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 10.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(m, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.63639f, 1.63639f, 1.63639f));
}

TEST(MaterialTest, SurfaceBetweenEL) {
    Material m;
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, 10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(m, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(.1f, .1f, .1f));
}