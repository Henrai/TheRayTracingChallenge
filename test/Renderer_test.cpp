#include <Camera.h>
#include <Tuple.h>
#include <Camera.h>
#include <Canvas.h>
#include <Renderer.h>
#include <Light.h>
#include <Shapes/Shape.h>
#include <Shapes/Sphere.h>
#include <World.h>

#include <gtest/gtest.h>
#include <cmath>

#include "TestUtil.h"

TEST(RendererTest, renderSample) {
    std::unique_ptr<World> world = defaultWorld();
    Camera camera(11,11, M_PI_2);
    camera.UpdateTransform(
        Tuple::Point(0.f, 0.f, -5.f),// from
        Tuple::Point(0.f, 0.f, 0.f), // to
        Tuple::Vector(0.f, 1.f, 0.f) // up
    );

    Renderer renderer;
    Canvas image = renderer.Render(*world.get(), camera);
    EXPECT_TRUE(image[5][5] == Color(.380637f, .475797f, .285478f));
}