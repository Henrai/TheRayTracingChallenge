#pragma once 

#include <World.h>
#include <Shapes/Shape.h>
#include <Shapes/Sphere.h>
#include <Shapes/Plane.h>
#include <Light.h>
#include <Color.h>

static std::unique_ptr<Shape> glass_sphere() {
    std::unique_ptr<Shape> shape = std::make_unique<Sphere>();
    shape->getMaterial().transparency = 1.0f;
    shape->getMaterial().refraction_index = 1.5f;
    return shape;
}

static std::shared_ptr<Shape> shared_glass_sphere() {
    std::shared_ptr<Shape> shape = std::make_shared<Sphere>();
    shape->getMaterial().transparency = 1.0f;
    shape->getMaterial().refraction_index = 1.5f;
    return shape;
}

static std::unique_ptr<World> defaultWorld() {
    std::unique_ptr<World> world = std::make_unique<World>();

    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10, 10,-10), 
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

static std::unique_ptr<World> defaultNoneReflectWorld() {
    std::unique_ptr<World> world = std::make_unique<World>();

    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
       PointLight(Tuple::Point(-10, 10,-10), 
        Color(1,1,1)));
    world->AddLight(light);

    std::shared_ptr<Shape> shape1 = std::make_shared<Sphere>();
    shape1->getMaterial().color = Color(0.8f, 1.0f, 0.6f);
    shape1->getMaterial().diffuse = 0.7f;
    shape1->getMaterial().specular = 0.2f;

    std::shared_ptr<Shape> shape2 = std::make_shared<Sphere>();
    shape2->getMaterial().ambient = 1.0f;
    shape2->SetTransform(matrix::Scale(0.5f, 0.5f, 0.5f));
    
    

    world->AddShape(shape1);
    world->AddShape(shape2);
    return world;   
}
