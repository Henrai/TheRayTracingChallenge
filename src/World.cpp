#include "Camera.h"
#include "Material.h"
#include "Matrix.h"
#include "Renderer.h"
#include "Shapes/Shape.h"
#include "Transformation.h"
#include "Tuple.h"
#include <World.h>
#include <Intersection.h>
#include <Color.h>
#include <Light.h>
#include <Ray.h>
#include <Renderer.h>
#include <Canvas.h>

#include <memory>
#include <string>
#include <vector>
#include <fstream>

#include<iostream>
using namespace std;

void World::AddCamera(Json::JSONObject obj) {

    int height = obj["height"].asInt();
    int width = obj["width"].asInt();
    double fov = obj["fov"].asDouble();
    mCamera = std::make_shared<Camera>(height, width, fov);
    auto from = obj["from"].asList();
    auto to = obj["to"].asList();
    auto up = obj["up"].asList();

    mCamera->UpdateTransform(
        Tuple::Point(
            from[0].asDouble(),
            from[1].asDouble(),
            from[2].asDouble()),
        Tuple::Point(
            to[0].asDouble(), 
            to[1].asDouble(), 
            to[2].asDouble()),
        Tuple::Vector(
            up[0].asDouble(), 
            up[1].asDouble(), 
            up[2].asDouble()));
}

void World::AddLights(Json::JSONObject map) {
    auto lights = map.asMap();
    for (auto [key, val] : lights) {
        AddLight(key, val);
    }
}

void World::AddLight(const std::string& name, Json::JSONObject obj) {
    auto point = obj["point"].asList();
    auto color = obj["color"].asList();
    auto light = std::make_shared<PointLight>(
        Tuple::Point(point[0].asDouble(), point[1].asDouble(), point[2].asDouble()),
        Color(color[0].asDouble(), color[1].asDouble(), color[2].asDouble()),
        name);
    AddLight(light);
}

void World::AddShapes(Json::JSONObject map) {
    auto shapes = map.asMap();
    for (auto [key, val]: shapes) {
        AddShape(key, val);
    }
}

void World::AddShape(const std::string& name, Json::JSONObject obj) {
    auto shape = Shape::getShape(name, obj["shape"].asString());
    shape->SetMaterial(Material(obj["material"]));
    auto transformation = Matrix4::Identity();
    auto tranformationMap = obj["transformation"];
    if (!tranformationMap.isMap()) {
       shape->SetTransform(transformation);
        AddShape(shape); 
        return;
    }

    for (auto [key, _] : tranformationMap.asMap()) {
        std::cout << key << std::endl;
    }
    auto scale = tranformationMap["scale"];
    if (scale.isList()) {
        auto scaleList = scale.asList();
        transformation = matrix::Scale(
            scaleList[0].asDouble(), 
            scaleList[1].asDouble(), 
            scaleList[2].asDouble()) * transformation;
    }
    auto rotateX = tranformationMap["rotationX"];
    if (rotateX.isDouble()) {
        std::cout << "rx\n";
        transformation = matrix::RotationX(rotateX.asDouble()) * transformation;
    }
    auto rotateY = tranformationMap["rotationY"];
    if (rotateY.isDouble()) {
        transformation = matrix::RotationY(rotateY.asDouble()) * transformation;
    }
    auto rotateZ = tranformationMap["rotationZ"];
    if (rotateZ.isDouble()) {
        transformation = matrix::RotationZ(rotateZ.asDouble()) * transformation;
    }
    auto trans = tranformationMap["translation"];
    if (trans.isList()) {
        std::cout << "trans\n";
        auto transList = trans.asList();
        transformation = matrix::Translation(
            transList[0].asDouble(), 
            transList[1].asDouble(),
            transList[2].asDouble()) * transformation;
    }
    shape->SetTransform(transformation);
    AddShape(shape);
}

bool World::LoadSecne(std::string_view file_name) {
    Json::JSONObject world = Json::JSONObject::fromFile(file_name);
    std::cout << world << endl;
    AddCamera(world["camera"]);
    mCamera->print();
    AddLights(world["lights"]);
    std::cout << "---------light----------\n";
    for(auto light : m_lights) {
        light->print();
    }
    AddShapes(world["shapes"]);
    std::cout << "------------shapes--------\n";
    for (auto shape : m_objects) {
        shape->print();
    }
    return true;
}

Color World::ShadeHit(const HitResult &hit, int remaining) const
{
    //cout << "okita shade hit" << endl;
    Color result = Color::BLACK;
    if (hit.shape == nullptr)
    {
        return result;
    }
    for (auto i : m_lights)
    {
        result = result + lighting::PhongLinghting(
             hit.shape, 
             *i, // light
             hit.overPoint, 
             hit.eyev, 
             hit.normalv, 
             IsShadowed(hit.overPoint, i));
    }
    
    Color reflectC = reflectedColor(hit, remaining);
    Color refractC = refracted_color(hit, remaining);

    if (hit.shape->getMaterial().reflective > 0 && hit.shape->getMaterial().transparency > 0) {
        double reflectance = hit.schlick();
        return result + reflectC * reflectance + refractC * (1 - reflectance);
    }

    return result + reflectedColor(hit, remaining) +  refracted_color(hit, remaining);
}

Color World::ColorAt(const Ray &ray, int remaining) const
{
    std::vector<Intersection> xs;
    this->Intersect(ray, xs);
    HitResult hit = Intersection::getHitResult(Intersection::Hit(xs), ray, xs);
    return this->ShadeHit(hit, remaining);
}

bool World::IsShadowed(const Tuple &point, std::shared_ptr<const PointLight> light) const
{
    Tuple l = light->position - point;

    double distance = l.Magnitude();
    Tuple dir = l.normalize();
    
    Ray r(point, dir);
    std::vector<Intersection> xs;
    this->Intersect(r, xs);
    Intersection hit = Intersection::Hit(xs);
    if (hit.Object() != nullptr && hit.Distance() >= 0.00001 && hit.Distance() < distance)
    {
        return true;
    }
    return false; 
}

Color World::reflectedColor(HitResult hitResult, int remaining) const {
    if(hitResult.shape->getMaterial().reflective < EPSILON || remaining <= 0) {
        return Color::BLACK;
    }
    Ray reflectRay(hitResult.overPoint, hitResult.reflectv);
    Color color = ColorAt(reflectRay, remaining - 1);
    return color * hitResult.shape->getMaterial().reflective;
}

Color World::refracted_color(HitResult hitResult, int remaining) const {
    

    double n_ratio = hitResult.n1 / hitResult.n2;
    double cos_i = hitResult.eyev.Dot(hitResult.normalv);
    double sin2_t = n_ratio * n_ratio * (1 - cos_i*cos_i);
    if (remaining == 0 || sin2_t > 1.0 || hitResult.shape->getMaterial().transparency == 0) {
        return Color(0, 0, 0);
    } else {
        

        double cos_t = sqrt(1 - sin2_t);
        auto dir = hitResult.normalv * (n_ratio * cos_i - cos_t) - hitResult.eyev * n_ratio;
        auto refract_ray = Ray(hitResult.underPoint, dir);
        Color refract_color = ColorAt(refract_ray, remaining - 1) * hitResult.shape->getMaterial().transparency;
       //if (remaining == 5) { 
        // cout << "== remaining " << remaining << " ==\n";
        // hitResult.toString();
        // cout << "n_ratio: " << n_ratio << endl;
        // cout << "cos_i: " << cos_i << endl;
        // cout << "sin2_t: " << sin2_t << endl;
        // cout << "cos_t: " << cos_t << endl;
        // cout << "refract dir: " << dir << endl;
        // cout << "refract color: " << refract_color << endl;
        // cout << endl << endl;
       //}
        return refract_color;
    }
}

void World::render() {
    Renderer renderer;

    Canvas canvas = renderer.Render(*this, *mCamera.get());

    ofstream out("scene.ppm");
    out<<canvas;
    out.close();
}