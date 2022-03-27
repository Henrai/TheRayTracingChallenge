#include <Camera.h>
#include <Matrix.h>
#include <Ray.h>

#include <cmath>
#include <gtest/gtest.h>

TEST(CameraTest, initializeCamera) {
    Camera camera(160, 120, M_PI_2);
    EXPECT_EQ(camera.getHorizontalSize(), 160);
    EXPECT_EQ(camera.getVerticalSize(), 120);
    EXPECT_FLOAT_EQ(camera.getFov(), M_PI_2);
    EXPECT_TRUE(camera.getTransformation() == Matrix4::Identity());
}

TEST(CameraTest, PixelSize) {
    Camera camera1(200, 125, M_PI_2);
    EXPECT_FLOAT_EQ(camera1.getPixelSize(), 0.01f);
    Camera camera2(125, 200, M_PI_2);
    EXPECT_FLOAT_EQ(camera2.getPixelSize(), 0.01f);
}

TEST(CameraTest, RayThroughCenter) {
    Camera camera(201, 101, M_PI_2);
    Ray r = camera.RayFromPixel(100, 50);
    EXPECT_TRUE(r.Origin() == Tuple::Point(0.f, 0.f, 0.f));
    EXPECT_TRUE(r.Direction() == Tuple::Vector(0.f, 0.f, -1.f));
}


TEST(CameraTest, RayThroughCorner) {
    Camera camera(201, 101, M_PI_2);
    Ray r = camera.RayFromPixel(0, 0);
    EXPECT_TRUE(r.Origin() == Tuple::Point(0.f, 0.f, 0.f));
    EXPECT_TRUE(r.Direction() == Tuple::Vector(.66519f, .33259f, -0.66851f));
}
