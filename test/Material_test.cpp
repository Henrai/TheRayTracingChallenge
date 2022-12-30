#include <Material.h>
#include <Color.h>
#include <Light.h>
#include <Tuple.h>
#include <Shapes/Sphere.h>
#include <Shapes/Shape.h>
#include <Patterns/StripePattern.h>

#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

#include <memory>

using namespace std;

std::shared_ptr<Shape> DefaultShape() {
    return std::make_shared<Sphere>();
}
TEST(MaterialTest, DefaultMaterial) {
    Material m;
    EXPECT_TRUE(m.color == Color::WHITE);
    EXPECT_FLOAT_EQ(m.ambient, 0.1f);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9f);
    EXPECT_FLOAT_EQ(m.specular, 0.9f);
    EXPECT_FLOAT_EQ(m.shininess, 200.0f);
    EXPECT_FLOAT_EQ(m.reflective, 0.0f);
}

TEST(MaterialTest, EyeBetweenLS) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.9f, 1.9f, 1.9f));
}


TEST(MaterialTest, EyeBetweenLSWithEOffset) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, sqrt(2.f)/2.f, -sqrt(2.f)/2.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.f, 1.f, 1.f));
}

TEST(MaterialTest, EyeBetweenLSWithLOffset) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 10.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(.7364f, .7364f, .7364f));
}

TEST(MaterialTest, SurfaceInShadow) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 10.f, -10.f), Color(1.f,1.f,1.f)};
    bool isShadowed = true;
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV, isShadowed);

    EXPECT_TRUE(result == Color::SHADOW);
}

TEST(MaterialTest, EyeBetweenLSWithLEReflect) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, -sqrt(2.f)/2.f, -sqrt(2.f)/2.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 10.f, -10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(1.63639f, 1.63639f, 1.63639f));
}

TEST(MaterialTest, SurfaceBetweenEL) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    Tuple position = Tuple::Point(0.f, 0.f, 0.f);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, 10.f), Color(1.f,1.f,1.f)};
    Color result = lighting::PhongLinghting(shape, light, position, eyeV, normalV);
    EXPECT_TRUE(result == Color(.1f, .1f, .1f));
}


TEST(MaterialTest, lightwithPattern) {
    std::shared_ptr<Shape> shape = DefaultShape(); 
    shape->getMaterial().ambient = 1;
    shape->getMaterial().diffuse = 0;
    shape->getMaterial().specular = 0;
    shape->getMaterial().pattern = std::make_shared<StripePattern>(Color::WHITE, Color::BLACK);

    Tuple eyeV = Tuple::Vector(0.f, 0.f, -1.f);
    Tuple normalV = Tuple::Vector(0.f, 0.f, -1.f);

    PointLight light  {Tuple::Point(0.f, 0.f, -10.f), Color(1.f,1.f,1.f)};
    Color c1 = lighting::PhongLinghting(shape, light, Tuple::Point(0.9f, 0.f, 0.f), eyeV, normalV);
    Color c2 = lighting::PhongLinghting(shape, light, Tuple::Point(1.1f, 0.f, 0.f), eyeV, normalV);
    EXPECT_TRUE(c1 == Color::WHITE);
    EXPECT_TRUE(c2 == Color::BLACK);
}