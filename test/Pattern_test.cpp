#include <Patterns/StripePattern.h>
#include <Patterns/GradientPattern.h>
#include <Patterns/CheckerPattern.h>
#include <Patterns/RingPattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>
#include <Shapes/Sphere.h>
#include <Transformation.h>

#include <gtest/gtest.h>
#include <iostream>

TEST(PatternTest, init) {
    StripePattern sp(Color::WHITE, Color::BLACK);
    EXPECT_TRUE(Color::WHITE == sp.first);
    EXPECT_TRUE(Color::BLACK == sp.second);
}

TEST(PatternTest, stripeY) {
    StripePattern sp(Color::WHITE, Color::BLACK); 
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,0,0)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,1,0)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,2,0)) == Color::WHITE);
}

TEST(PatternTest, stripeZ) {
    StripePattern sp(Color::WHITE, Color::BLACK); 
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,0,0)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,0,1)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,0,2)) == Color::WHITE);
}


TEST(PatternTest, stripeX) {
    StripePattern sp(Color::WHITE, Color::BLACK); 
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0,0,0)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(0.9,0,0)) == Color::WHITE);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(1,0,0)) == Color::BLACK);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(-0.1,0,0)) == Color::BLACK);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(-1,0,0)) == Color::BLACK);
    EXPECT_TRUE(sp.PatternAt(Tuple::Point(-1.1,0,0)) == Color::WHITE);
}

TEST(PatternTest, objectTransformOnly) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->SetTransform(matrix::Scale(2, 2, 2));
    StripePattern sp(Color::WHITE, Color::BLACK);
    EXPECT_TRUE(sp.PatternAtShape(shape, Tuple::Point(1.5,0, 0)) == Color::WHITE); 
}

TEST(PatternTest, PatternTransformOnly) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    StripePattern sp(Color::WHITE, Color::BLACK);
    sp.transform = matrix::Scale(2,2,2);
    EXPECT_TRUE(sp.PatternAtShape(shape, Tuple::Point(1.5,0, 0)) == Color::WHITE); 
}

TEST(PatternTest, PatternAndObjectTransform) {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->SetTransform(matrix::Scale(2, 2, 2));
    StripePattern sp(Color::WHITE, Color::BLACK);
    sp.transform = matrix::Translation(0.5, 0, 0);
    EXPECT_TRUE(sp.PatternAtShape(shape, Tuple::Point(2.5,0, 0)) == Color::WHITE); 
}

TEST(PatternTest, RingPattern) {
    RingPattern rp(Color::WHITE, Color::BLACK);
    EXPECT_TRUE(rp.PatternAt(Tuple::Point(0,0,0)) == Color::WHITE);
    EXPECT_TRUE(rp.PatternAt(Tuple::Point(1,0,0)) == Color::BLACK);
    EXPECT_TRUE(rp.PatternAt(Tuple::Point(0,0,1)) == Color::BLACK);
    EXPECT_TRUE(rp.PatternAt(Tuple::Point(0.708,0,0.708)) == Color::BLACK); 
}