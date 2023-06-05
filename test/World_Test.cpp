#include <World.h>
#include <Tuple.h>
#include <Transformation.h>
#include <Shapes/Sphere.h>
#include <Light.h>
#include <Material.h>
#include <Color.h>
#include <Patterns/StripePattern.h>

#include <gtest/gtest.h>
#include <cmath>

#include <memory>

#include "Intersection.h"
#include "Patterns/Pattern.h"
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
    EXPECT_TRUE(c == Color(0.380637f, 0.475797f, 0.285478f));
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
    EXPECT_TRUE(c == Color(0.904662, 0.904662f, 0.904662f));
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
    cout << c << endl;
    EXPECT_TRUE(c == Color(0.380637f, 0.475797f, 0.285478f));
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

TEST(WorldTest, noreflectiveSurface) {
    std::unique_ptr<World> world = defaultNoneReflectWorld();
    Ray r(Tuple::Point(0,0,0), Tuple::Vector(0,0,1));
    auto s = world->getObjects()[1];
    Intersection i(s, 1.f);
    HitResult hit = Intersection::getHitResult(i,r);
    Color reflect_color = world->reflectedColor(hit);

    EXPECT_TRUE(reflect_color == Color(0.f, 0.f, 0.f));
}

TEST(WorldTest, reflectedColorForReflectedM) {
    std::unique_ptr<World> world = defaultNoneReflectWorld();

    std::shared_ptr<Shape> shape3 = std::make_shared<Plane>();
    shape3->getMaterial().reflective = 0.5;
    shape3->SetTransform(matrix::Translation(0,-1,0));
    world->AddShape(shape3);

    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, - sqrt(2.f)/2.f, sqrt(2.f)/2.0f));
    Intersection i(shape3, sqrt(2.f));
    HitResult hit = Intersection::getHitResult(i,r);
    Color reflect_color = world->reflectedColor(hit);
    cout << reflect_color << endl;
    EXPECT_TRUE(reflect_color == Color(0.190491f, 0.238114f, 0.142868f)); 
}

TEST(WorldTest, shadeHitWithReflect) {
    std::unique_ptr<World> world = defaultNoneReflectWorld();

    std::shared_ptr<Shape> shape3 = std::make_shared<Plane>();
    shape3->getMaterial().reflective = 0.5;
    shape3->SetTransform(matrix::Translation(0,-1,0));
    world->AddShape(shape3);

    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, - sqrt(2.f)/2.f, sqrt(2.f)/2.0f));
    Intersection i(shape3, sqrt(2.f));
    HitResult hit = Intersection::getHitResult(i,r);
    Color shade = world->ShadeHit(hit);
    cout << shade << endl;
    EXPECT_TRUE(shade == Color(0.876886f, 0.924509f, 0.829263f)); 
}

TEST(WorldTest, mutuallyReflect) {
    std::unique_ptr<World> world = std::make_unique<World>();
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(0, 0, 0), Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape1 = std::make_shared<Sphere>();
    shape1->getMaterial().reflective = 1.f;
    shape1->SetTransform(matrix::Translation(0, -1, 0));
    std::shared_ptr<Shape> shape2 = std::make_shared<Sphere>();
    shape2->getMaterial().reflective = 1.f;
    shape2->SetTransform(matrix::Translation(0, 1, 0));

    world->AddShape(shape1);
    world->AddShape(shape2);

    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 1, 0));

    world->ColorAt(r);
}

TEST(WorldTest, refractColorAtOpaqueSurface) {
    std::unique_ptr<World> world = defaultWorld();
    auto shape = world->getObjects()[0];
    Ray r(Tuple::Point(0,0, -5), Tuple::Vector(0,0,1));
    std::vector<Intersection> xs {{shape, 4}, {shape, 6}};
    HitResult hit = Intersection::getHitResult(xs[0], r, xs);
    Color c = world->refracted_color(hit);
    EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(WorldTest, refractColorWithMaxDepth) {
   std::unique_ptr<World> world = std::make_unique<World>();

   std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10, 10,-10), 
        Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    shape->getMaterial().diffuse = 0.7f;
    shape->getMaterial().specular = 0.2f;
    shape->getMaterial().transparency = 1.0f;
    shape->getMaterial().refraction_index = 1.5f;

    world->AddShape(shape);

    Ray r(Tuple::Point(0,0, -5), Tuple::Vector(0,0,1));
    std::vector<Intersection> xs {{shape, 4}, {shape, 6}};
    HitResult hit = Intersection::getHitResult(xs[0], r, xs);
    Color c = world->refracted_color(hit, 0);
    EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(WorldTest, totalInternalReflection) {
    std::unique_ptr<World> world = std::make_unique<World>();

   std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10, 10,-10), 
        Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    shape->getMaterial().diffuse = 0.7f;
    shape->getMaterial().specular = 0.2f;
    shape->getMaterial().transparency = 1.0f;
    shape->getMaterial().refraction_index = 1.5f;

    world->AddShape(shape);

    Ray r(Tuple::Point(0,0, 0.7071068), Tuple::Vector(0,1,0));
    std::vector<Intersection> xs {{shape, -0.7071068}, {shape, 0.7071068}};
    HitResult hit = Intersection::getHitResult(xs[1], r, xs);
    Color c = world->refracted_color(hit, 5);
    EXPECT_TRUE(c == Color(0, 0, 0));
}


TEST(WorldTest, computeRefractionColor) {
    std::unique_ptr<World> world = std::make_unique<World>();

   std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(0, 0, 0),  Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> A = std::make_shared<Sphere>();
    A->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    A->getMaterial().diffuse = 0.7f;
    A->getMaterial().specular = 0.2f;
    A->getMaterial().ambient = 1.0f;
    A->getMaterial().pattern = make_shared<StripePattern>(Color::WHITE, Color::BLACK);

    std::shared_ptr<Shape> B = std::make_shared<Sphere>();
    B->getMaterial().ambient = 1.0f;
    B->getMaterial().transparency = 1.0f;
    B->getMaterial().refraction_index = 1.5f;
    B->SetTransform(matrix::Scale(0.5f, 0.5f, 0.5f));

    world->AddShape(A); world->AddShape(B);
    

    Ray r(Tuple::Point(0,0, .1), Tuple::Vector(0,1,0));
    std::vector<Intersection> xs {{A, -0.9899}, {B, -.4899}, {B, .4899}, {A, 9899}};
    HitResult hit = Intersection::getHitResult(xs[2], r, xs);
    
    Color c = world->refracted_color(hit, 5);
    cout <<"okita " << c << endl;
    EXPECT_TRUE(c == Color(0, 0.99888, 0.04725));
}