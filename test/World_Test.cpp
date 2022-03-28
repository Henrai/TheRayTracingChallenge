#include <World.h>
#include <Tuple.h>
#include <Transformation.h>
#include <Sphere.h>
#include <Light.h>
#include <Material.h>

#include <gtest/gtest.h>
#include <cmath>

#include <memory>

#include "TestUtil.h"

#include <iostream>
using namespace std;

TEST(WorldTest, EmptyWorld) {
    std::unique_ptr<World> world = std::make_unique<World>();
    EXPECT_EQ(world->getObjects().size(), 0);
    EXPECT_EQ(world->getLights().size(), 0);
}

TEST(WorldTest, DefaultWorld) {
    std::unique_ptr<World> world = defaultWorld();
    EXPECT_EQ(world->getObjects().size(), 2);
    EXPECT_EQ(world->getLights().size(), 1);
}

TEST(WorldTest, IntersectWorld) {
    std::unique_ptr<World> world = defaultWorld();
    Ray ray(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    std::vector<Intersection> xs;
    world->Intersect(ray, xs);
    std::sort(xs.begin(), xs.end());

    EXPECT_FLOAT_EQ(xs.size(), 4.f);
    EXPECT_FLOAT_EQ(xs[0].Distance(), 4.f);
    EXPECT_FLOAT_EQ(xs[1].Distance(), 4.5f);
    EXPECT_FLOAT_EQ(xs[2].Distance(), 5.5f);
    EXPECT_FLOAT_EQ(xs[3].Distance(), 6.f);
}

TEST(WorldTest, ShadingAtIntersect) {
    std::unique_ptr<World> world = defaultWorld();
    Ray ray(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    auto shape1 = world->getObjects()[0];
    Intersection intersect(shape1, 4.f);
    HitResult hit = Intersection::getHitResult(intersect, ray);
    Color c = world->ShadeHit(hit);
    cout << c <<endl;
    EXPECT_TRUE(c == Color(0.38066f, 0.47583f, 0.2854959f));
}

TEST(WorldTest, ShadingAtIntersectInside) {
    std::unique_ptr<World> world = defaultWorld();
    world->clearLight();
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(0.f, .25f, 0.f), 
        Color(1,1,1)));

    world->AddLight(light);
    Ray ray(Tuple::Point(0.f, 0.f, 0.f), Tuple::Vector(0.f, 0.f, 1.f));
    auto shape1 = world->getObjects()[1];
    Intersection intersect(shape1, .5f);
    HitResult hit = Intersection::getHitResult(intersect, ray);
    Color c = world->ShadeHit(hit);
    cout << c <<endl;
    EXPECT_TRUE(c == Color(0.90498, 0.90498f, 0.90498f));
}

TEST(WorldTest, RayMiss) {
    std::unique_ptr<World> world = defaultWorld();
    Ray ray(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 1.f, 0.f));
    Color c = world->ColorAt(ray);

    EXPECT_TRUE(c == Color::BLACK);
}

TEST(WorldTest, RayHit) {
    std::unique_ptr<World> world = defaultWorld();
    Ray ray(Tuple::Point(0.f, 0.f, -5.f), Tuple::Vector(0.f, 0.f, 1.f));
    Color c = world->ColorAt(ray);

    EXPECT_TRUE(c == Color(0.38066f, 0.47583f, 0.28549f));
}

TEST(WorldTest, intersectionBehindRay) {
    std::unique_ptr<World> world = std::make_unique<World>();

    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10, 10, -10), 
        Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape1 = std::make_shared<Sphere>();
    shape1->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    shape1->getMaterial().diffuse = 0.7f;
    shape1->getMaterial().specular = 0.2f;
    shape1->getMaterial().ambient = 1.f;

    std::shared_ptr<Shape> shape2 = std::make_shared<Sphere>();
    shape2->getMaterial().ambient = 1.f;
    shape2->SetTransform(matrix::Scale(0.5f, 0.5f, 0.5f));
    world->AddShape(shape1);
    world->AddShape(shape2);

    Ray ray(Tuple::Point(0.f, 0.f,.75f), Tuple::Vector(0.f, 0.f, -1.f));

    Color c = world->ColorAt(ray);
    EXPECT_TRUE(c == shape2->getMaterial().color);
}

TEST(WorldTest, NoShadowAndNoHit) {
    std::unique_ptr<World> world = defaultWorld();
    auto light = world->getLights()[0];
    Tuple point = Tuple::Point(0,10,0);
    EXPECT_FALSE(world->IsShadowed(point, light));
}

TEST(WorldTest, HasShadow) {
    std::unique_ptr<World> world = defaultWorld();
    auto light = world->getLights()[0];
    Tuple point = Tuple::Point(10, -10, 10);
    EXPECT_TRUE(world->IsShadowed(point, light));
}

TEST(WorldTest, NoShadowObjectBehindLight) {
    std::unique_ptr<World> world = defaultWorld();
    auto light = world->getLights()[0];
    Tuple point = Tuple::Point(-20, 20, -20);
    EXPECT_FALSE(world->IsShadowed(point, light));
}

TEST(WorldTest, NoShadowObjectBehindPoint) {
    std::unique_ptr<World> world = defaultWorld();
    auto light = world->getLights()[0];
    Tuple point = Tuple::Point(-2, 2, -2);
    EXPECT_FALSE(world->IsShadowed(point, light));
}