#include <World.h>
#include <Tuple.h>
#include <Transformation.h>
#include <Sphere.h>
#include <Light.h>
#include <Material.h>

#include <gtest/gtest.h>
#include <cmath>

#include <memory>

std::unique_ptr<World> defaultWorld() {
    std::unique_ptr<World> world = std::make_unique<World>();

    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10,-10,-10), 
        Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape1 = std::make_shared<Sphere>();
    shape1->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    shape1->getMaterial().diffuse = 0.7f;
    shape1->getMaterial().specular = 0.2f;
    std::shared_ptr<Shape> shape2 = std::make_shared<Sphere>();
    shape2->SetTransform(matrix::Scale(0.5f, 0.5f, 0.5f));
    world->AddShape(shape1);
    world->AddShape(shape2);
    return world;   
}

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