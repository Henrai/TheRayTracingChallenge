#include <Shapes/Shape.h>
#include <World.h>
#include <Material.h>
#include <Light.h>
#include <Transformation.h>
#include <Camera.h>
#include <Renderer.h>
#include <Shapes/Sphere.h>
#include <Canvas.h>

#include <cmath>
#include <memory>
#include <fstream>

#define H_SIZE 1080
#define V_SIZE 720

int main() {
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
        PointLight(Tuple::Point(-10, 10,-10), 
        Color(1,1,1)));
    
    // set up floor
    std::shared_ptr<Shape> floor = std::make_shared<Sphere>();
    floor->SetTransform(matrix::Scale(10.f, 0.01f, 10.f));
    floor->getMaterial().color = Color(1.f, 0.9f, 0.9f);
    floor->getMaterial().specular = .0f;

    // set up left wall
    std::shared_ptr<Shape> leftWall = std::make_shared<Sphere>();
    leftWall->SetTransform(
        matrix::Translation(0.f, 0.f, 5.f) 
      * matrix::RotationY(-M_PI_4) 
      * matrix::RotationX(M_PI_2) 
      * matrix::Scale(10.f, 0.01f, 10.f));
    leftWall->getMaterial() = floor->getMaterial();
    //leftWall->getMaterial().color = Color::GREEN;

    // set up right wall
    std::shared_ptr<Shape> rightWall = std::make_shared<Sphere>();
    rightWall->SetTransform(
        matrix::Translation(0.f, 1.f, 5.f) 
      * matrix::RotationY(M_PI_4) 
      * matrix::RotationX(M_PI_2) 
      * matrix::Scale(10.f, 0.01f, 10.f));
    rightWall->getMaterial() = floor->getMaterial();
    //rightWall->getMaterial().color = Color::RED;

    // set up middle ball
    std::shared_ptr<Shape> middleBall = std::make_shared<Sphere>();
    middleBall->SetTransform(matrix::Translation(-0.5f, 1.f, 0.5f));
    middleBall->getMaterial().color = Color(0.1f, 1.f, 0.5f);
    middleBall->getMaterial().diffuse = .7f;
    middleBall->getMaterial().specular = .3f;

    // set up left ball 
    std::shared_ptr<Shape> leftBall = std::make_shared<Sphere>();
    leftBall->SetTransform(matrix::Translation(1.5f, .5f, -0.5f) * matrix::Scale(0.5, 0.5, 0.5));
    leftBall->getMaterial().color = Color(0.5f, 1.f, 0.1f);
    leftBall->getMaterial().diffuse = .7f;
    leftBall->getMaterial().specular = .3f;

    // set up right ball
    std::shared_ptr<Shape> rightBall = std::make_shared<Sphere>();
    rightBall->SetTransform(matrix::Translation(-1.5f, .33f, -0.75f) * matrix::Scale(0.33f, 0.33f, 0.33f));
    rightBall->getMaterial().color = Color(1.f, .8f, 0.1f);
    rightBall->getMaterial().diffuse = .7f;
    rightBall->getMaterial().specular = .3f;

    std::unique_ptr<World> world = std::make_unique<World>();

    world->AddLight(light);

    world->AddShape(floor);
    world->AddShape(leftWall);
    world->AddShape(rightWall);
    world->AddShape(leftBall);
    world->AddShape(middleBall);
    world->AddShape(rightBall);

    Camera camera(H_SIZE, V_SIZE, M_PI/3.f);
    camera.UpdateTransform(
        Tuple::Point(0.f, 1.5f, -5.f), // from
        Tuple::Point(0.f, 1.f, 0.f),   // To
        Tuple::Vector(0.f, 1.f, 0.f)   // up
    );

    Renderer renderer;

    Canvas canvas = renderer.Render(*world.get(), camera);

    ofstream out("scene.ppm");
    out<<canvas;
    out.close();
    return 0;
}