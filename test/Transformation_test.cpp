#include <Matrix.h>
#include <Tuple.h>
#include <Transformation.h>
#include <cmath>
#include <gtest/gtest.h>

TEST(TransTest, translationActOnPoint)
{
    Matrix4 tx = matrix::Translation(5.f, -3.f, 2.f);
    Tuple p = Tuple::Point(-3.f, 4.f, 5.f);
    EXPECT_TRUE( tx * p == Tuple::Point(2.f, 1.f, 7.f));
}

TEST(TransTest, translationActInverseOnPoint )
{
    Matrix4 tx = matrix::Translation(5.f, -3.f, 2.f);
    Tuple p = Tuple::Point(-3.f, 4.f, 5.f);
    EXPECT_TRUE( tx.Inverse() * p == Tuple::Point(-8.f, 7.f, 3.f));
}

TEST(TransTest, translationActOnVector)
{
    Matrix4 tx = matrix::Translation(5.f, -3.f, 2.f);
    Tuple v = Tuple::Vector(-3.f, 4.f, 5.f);
    EXPECT_TRUE( tx * v == v );
}

TEST(TransTest, scaleActOnPoint)
{
    Matrix4 tx = matrix::Scale(2.f, 3.f, 4.f);
    Tuple p = Tuple::Point(-4.f, 6.f, 8.f);
    EXPECT_TRUE(tx * p == Tuple::Point(-8.f, 18.f, 32.f));
}

TEST(TransTest, scaleActInverseOnVector)
{
    Matrix4 tx = matrix::Scale(2.f, 3.f, 4.f);
    Tuple v = Tuple::Vector(-4.f, 6.f, 8.f);
    EXPECT_TRUE( tx * v == Tuple::Vector(-8.f, 18.f, 32.f) );
}

TEST(TransTest, scaleActOnVector)
{
    Matrix4 tx = matrix::Scale(2.f, 3.f, 4.f);
    Tuple v = Tuple::Vector(-4.f, 6.f, 8.f);
    EXPECT_TRUE( tx.Inverse() * v == Tuple::Vector(-2.f, 2.f, 2.f) );
}

TEST(TransTest, rotateAroundX)
{
    Matrix4 halfquater = matrix::RotationX(M_PI_4);
    Matrix4 fullquater = matrix::RotationX(M_PI_2);
    Tuple p = Tuple::Point(0.f, 1.f, 0.f);
    EXPECT_TRUE(halfquater * p == Tuple::Point(0.f, sqrt(2.f) / 2.f, sqrt(2.f) / 2.f));
    EXPECT_TRUE(fullquater * p == Tuple::Point(0.f, 0.f, 1.f));
}


TEST(TransTest, rotateAroundY)
{
    Matrix4 halfquater = matrix::RotationY(M_PI_4);
    Matrix4 fullquater = matrix::RotationY(M_PI_2);
    Tuple p = Tuple::Point(0.f, 0.f, 1.f);
    EXPECT_TRUE(halfquater * p == Tuple::Point(sqrt(2.f) / 2.f, 0.f, sqrt(2.f) / 2.f));
    EXPECT_TRUE(fullquater * p == Tuple::Point(1.f, 0.f, 0.f));
}

TEST(TransTest, rotateAroundZ)
{
    Matrix4 halfquater = matrix::RotationZ(M_PI_4);
    Matrix4 fullquater = matrix::RotationZ(M_PI_2);
    Tuple p = Tuple::Point(0.f, 1.f, 0.f);
    EXPECT_TRUE(halfquater * p == Tuple::Point(-sqrt(2.f) / 2.f, sqrt(2.f) / 2.f, 0.f));
    EXPECT_TRUE(fullquater * p == Tuple::Point(-1.f, 0.f, 0.f));
}


TEST(TransTest,  shearXY)
{
    Matrix4 tx = matrix::Shear(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(5.f, 3.f, 4.f));
}

TEST(TransTest,  shearXZ)
{
    Matrix4 tx = matrix::Shear(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(6.f, 3.f, 4.f));
}

TEST(TransTest,  shearYX)
{
    Matrix4 tx = matrix::Shear(0.f, 0.f, 1.f, 0.f, 0.f, 0.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(2.f, 5.f, 4.f));
}

TEST(TransTest,  shearYZ)
{
    Matrix4 tx = matrix::Shear(0.f, 0.f, 0.f, 1.f, 0.f, 0.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(2.f, 7.f, 4.f));
}

TEST(TransTest,  shearZX)
{
    Matrix4 tx = matrix::Shear(0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(2.f, 3.f, 6.f));
}

TEST(TransTest,  shearZY)
{
    Matrix4 tx = matrix::Shear(0.f, 0.f, 0.f, 0.f, 0.f, 1.f);
    Tuple p = Tuple::Point(2.f, 3.f, 4.f);
    EXPECT_TRUE(tx * p == Tuple::Point(2.f, 3.f, 7.f));
}

TEST(TransTest,  multiolyInSequence)
{
    Tuple p = Tuple::Point(1.f, 0.f, 1.f);
    Matrix4 a = matrix::RotationX(M_PI_2);
    Matrix4 b = matrix::Scale(5.f, 5.f, 5.f);
    Matrix4 c = matrix::Translation(10.f, 5.f, 7.f);
    Tuple p2 = a * p;
    Tuple p3 = b * p2;
    Tuple p4 = c * p3;
    EXPECT_TRUE(p2 == Tuple::Point(1.f, -1.f, 0.f));
    EXPECT_TRUE(p3 == Tuple::Point(5.f, -5.f, 0.f));
    EXPECT_TRUE(p4 == Tuple::Point(15.f, 0.f, 7.f));
}

TEST(TransTest,  multiolyAppliedInReversedOrder)
{
    Tuple p = Tuple::Point(1.f, 0.f, 1.f);
    Matrix4 a = matrix::RotationX(M_PI_2);
    Matrix4 b = matrix::Scale(5.f, 5.f, 5.f);
    Matrix4 c = matrix::Translation(10.f, 5.f, 7.f);
    Matrix4 tx = c*b*a;
    EXPECT_TRUE( tx * p == Tuple::Point(15.f, 0.f, 7.f));
}