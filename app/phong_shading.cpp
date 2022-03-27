#include <iostream>
#include <Tuple.h>
#include <MathUtil.h>
#include <Color.h>
#include <Canvas.h>
#include <Sphere.h>
#include <Shape.h>
#include <Material.h>
#include <Light.h>

#include <fstream>
#include <vector>

int main() {
    size_t canva_size = 300.f;
    Canvas canvas(canva_size, canva_size);
    Tuple rayOrigin = Tuple::Point(0.f, 0.f, -5.f);

    float wall_z = 10.f;
    float wall_size = 7.f;
    float pixel_size = wall_size / (float) canva_size;
    float half = wall_size / 2.f;

    Color c = Color::RED;

    auto sphere = std::make_shared<Sphere>();
    sphere->getMaterial().color = Color(1.f, 0.2f, 1.f);

    PointLight light = {Tuple::Point(-10.f, 10.f, -10.f), Color(1.f, 1.f, 1.f)};

    for (size_t i = 0; i < canva_size; i++) {
        float world_y = half - pixel_size * (float)i;
        for ( size_t j = 0; j < canva_size; j++) {
            float world_x = -half + pixel_size * (float)j;

            Tuple pos = Tuple::Point(world_x, world_y, wall_z);
            Ray r = Ray(rayOrigin, (pos - rayOrigin).normalize());
            std::vector<Intersection> xs;
            sphere->Intersect(r, xs);

            Intersection hit = Intersection::Hit(xs);
        
            std::cout<<xs.size()<<std::endl;
            for (auto q : xs) {
                std::cout << q.Distance() <<" ";
            }

            if (hit.Object() != nullptr) {

                Tuple position = r.Position(hit.Distance());
                Tuple normal = hit.Object()->NormalAt(position);
                Tuple eye = -r.Direction();

                canvas[i][j] = lighting::PhongLinghting(hit.Object()->getMaterial(), light, position, eye, normal);
            }
        }
    }

    std::ofstream out("phong_shading.ppm");
    out<<canvas;
    out.close();

    return 0;
}