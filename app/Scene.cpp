#include "Color.h"
#include <Shapes/Shape.h>
#include <World.h>
#include <Material.h>
#include <Light.h>
#include <Transformation.h>
#include <Camera.h>
#include <Renderer.h>
#include <Shapes/Sphere.h>
#include <Shapes/Plane.h>
#include <Canvas.h>
#include <Patterns/StripePattern.h>
#include <Patterns/GradientPattern.h>
#include <Patterns/CheckerPattern.h>
#include <Patterns/RingPattern.h>

#include <cmath>
#include <memory>
#include <fstream>

#define H_SIZE 512
#define V_SIZE 512

int main() {
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
        PointLight(Tuple::Point(2, 10, -5), 
        Color(0.9, 0.9, 0.9)));
    
    // set up floor
    std::shared_ptr<Shape> floor = std::make_shared<Plane>();
    floor->SetTransform(matrix::Translation(0, 0, 10) * matrix::RotationX(1.5708));
    floor->getMaterial().ambient = 0.8;
    floor->getMaterial().diffuse = 0.2;
    floor->getMaterial().specular = 0;
    floor->getMaterial().pattern = std::make_shared<CheckerPattern>(Color(.15,.15,.15), Color(.85,.85,.85));

    
    auto biggger = std::make_shared<Sphere>();
    biggger->getMaterial().ambient = 0.0;
    biggger->getMaterial().diffuse = 0.0;
    biggger->getMaterial().specular = 0.9;
    biggger->getMaterial().reflective = 0.9;
    biggger->getMaterial().shininess = 300;
    biggger->getMaterial().transparency = 0.9;
    biggger->getMaterial().refraction_index = 1.5;
    biggger->getMaterial().color = Color(1,1,1);

    auto smaller= std::make_shared<Sphere>();
    smaller->SetTransform(matrix::Scale(0.5, 0.5, 0.5));
    smaller->getMaterial().ambient = 0.0;
    smaller->getMaterial().diffuse = 0.0;
    smaller->getMaterial().specular = 0.9;
    smaller->getMaterial().reflective = 0.9;
    smaller->getMaterial().transparency = 0.9;
    smaller->getMaterial().shininess = 300;
    smaller->getMaterial().refraction_index = 1.0000034;
    smaller->getMaterial().color = Color(1,1,1);
    

    std::unique_ptr<World> world = std::make_unique<World>();

    world->AddLight(light);

    world->AddShape(floor);
    world->AddShape(biggger);
    world->AddShape(smaller);

    Camera camera(H_SIZE, V_SIZE, 0.45);
    camera.UpdateTransform(
        Tuple::Point(0.f, 0.f, -5),    // from
        Tuple::Point(0.f, 0.f, 0.f),   // To
        Tuple::Vector(0.f, 1.f, 0.f)   // up
    );

    Renderer renderer;

    Canvas canvas = renderer.Render(*world.get(), camera);

    ofstream out("scene.ppm");
    out<<canvas;
    out.close();
    return 0;
}