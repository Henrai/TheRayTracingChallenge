#include <gtest/gtest.h>
#include <Tuple.h>
#include <cmath>

// Demonstrate some basic assertions.
TEST(TupleTest, TupleIsPoint) {
  Tuple t(4.3f, -4.2f, 3.1f, 1.0f);
   EXPECT_EQ(t.IsPoint(), true);
}

TEST(TupleTest, TupleIsVector) {
  Tuple t(4.3f, -4.2f, 3.1f, 0.0f);
   EXPECT_EQ(t.IsVector(), true);
}

TEST(TupleTest, createPoint) {
    Tuple t = Tuple::Point(4, -4, 3);
    EXPECT_TRUE( t == Tuple(4, -4, 3, 1));
}

TEST(TupleTest, createVector) {
    Tuple t = Tuple::Vector(4, -4, 3);
    EXPECT_TRUE( t == Tuple(4, -4, 3, 0));
}

TEST(TupleTest, addingTwoTuples) {
    Tuple t1 = Tuple(3, -2, 5, 1);
    Tuple t2 = Tuple(-2, 3, 1, 0);
    EXPECT_TRUE( t1 + t2 == Tuple(1, 1, 6, 1));
}

TEST(TupleTest, subtractingTwoPoints) {
    Tuple t1 = Tuple::Point(3, 2, 1);
    Tuple t2 = Tuple::Point(5, 6, 7);
    Tuple t3 = t1 - t2;

    EXPECT_TRUE(t3 == Tuple::Vector(-2, -4, -6));
    EXPECT_TRUE(t3.IsVector());
}

TEST(TupleTest, subtractingVectorFromPoint) {
    Tuple t1 = Tuple::Point(3, 2, 1);
    Tuple t2 = Tuple::Vector(5, 6, 7);
    Tuple t3 = t1 - t2;

    EXPECT_TRUE(t3 == Tuple::Point(-2, -4, -6));
    EXPECT_TRUE(t3.IsPoint());
}

TEST(TupleTest, subtractingVectorFromVector) {
    Tuple t1 = Tuple::Vector(3, 2, 1);
    Tuple t2 = Tuple::Vector(5, 6, 7);
    Tuple t3 = t1 - t2;

    EXPECT_TRUE(t3 == Tuple::Vector(-2, -4, -6));
    EXPECT_TRUE(t3.IsVector());
}

TEST(TupleTest, negatingATuple) {
    Tuple t = Tuple(1, -2, 3, -4);
    EXPECT_TRUE (-t == Tuple(-1,2,-3,4));
}

TEST(TupleTest, multiplyByScalar) {
    Tuple t = Tuple(1, -2, 3, -4);
    EXPECT_TRUE ( t * 3.5f  == Tuple(3.5f, -7.0f, 10.5f, -14.0f));
    EXPECT_TRUE ( t * 0.5f  == Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST(TupleTest, divideByScalar) {
    Tuple t = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    EXPECT_TRUE ( t / 2  == Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST(TupleTest, magnitude) {
    Tuple t1= Tuple::Vector(1.0f, 0.0f, 0.0f);
    Tuple t2= Tuple::Vector(0.0f, 1.0f, 0.0f);
    Tuple t3= Tuple::Vector(0.f, 0.0f, 1.0f);
    Tuple t4= Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple t5= Tuple::Vector(-1.0f, -2.0f, -3.0f);

    EXPECT_FLOAT_EQ(t1.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(t2.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(t3.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(t4.Magnitude(), std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(t5.Magnitude(), std::sqrt(14.0f));
}

TEST(TupleTest, normalize) {
    Tuple t1 = Tuple::Vector(4.0f, 0.0f ,0.0f);
    EXPECT_TRUE (t1.normalize() == Tuple::Vector(1.0f, 0.0f, 0.0f));
    Tuple t2 = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple t2n = t2.normalize();
    EXPECT_TRUE(t2n == Tuple::Vector(0.26726f, 0.53452f, 0.80178f));
    EXPECT_FLOAT_EQ(t2n.Magnitude(), 1.0f);

}

TEST(TupleTest, dot) {
    Tuple t1 = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple t2 = Tuple::Vector(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(t1.Dot(t2), 20.0f);
}

TEST(TupleTest, cross) {
    Tuple t1 = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple t2 = Tuple::Vector(2.0f, 3.0f, 4.0f);
    EXPECT_TRUE (t1.Cross(t2) == Tuple::Vector(-1.0f, 2.0f, -1.0f));
    EXPECT_TRUE (t2.Cross(t1) == Tuple::Vector(1.0f, -2.0f, 1.0f));
}

TEST(TupleTest, reflecting) {
    Tuple in = Tuple::Vector(1.f, -1.f, 0.f);
    Tuple n = Tuple::Vector(0.f, 1.f, 0.f);
    EXPECT_TRUE(in.Reflect(n) == Tuple::Vector(1.f,1.f,0.f));

    Tuple in2 = Tuple::Vector(0.f, -1.f, 0.f);
    Tuple n2 = Tuple::Vector(sqrtf(2.f)/2.f, sqrtf(2.f)/2.f, 0.f);
    EXPECT_TRUE(in2.Reflect(n2) == Tuple::Vector(1.f,0.f,0.f));
}
