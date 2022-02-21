#include <gtest/gtest.h>
#include <Tuple.h>
#include <cmath>

// Demonstrate some basic assertions.
TEST(TupleTest, TupleIsPoint) {
  Tuple t(4.3, -4.2, 3.1, 1.0);
   EXPECT_EQ(t.IsPoint(), true);
}

TEST(TupleTest, TupleIsVector) {
  Tuple t(4.3, -4.2, 3.1, 0.0);
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
    EXPECT_TRUE ( t * 3.5  == Tuple(3.5, -7, 10.5, -14));
    EXPECT_TRUE ( t * 0.5  == Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, divideByScalar) {
    Tuple t = Tuple(1, -2, 3, -4);
    EXPECT_TRUE ( t / 2  == Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, magnitude) {
    Tuple t1= Tuple::Vector(1, 0, 0);
    Tuple t2= Tuple::Vector(0, 1, 0);
    Tuple t3= Tuple::Vector(0, 0, 1);
    Tuple t4= Tuple::Vector(1, 2, 3);
    Tuple t5= Tuple::Vector(-1, -2, -3);

    EXPECT_DOUBLE_EQ(t1.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(t2.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(t3.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(t4.Magnitude(), std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(t5.Magnitude(), std::sqrt(14.0));
}

TEST(TupleTest, normalize) {
    Tuple t1 = Tuple::Vector(4, 0 ,0);
    EXPECT_TRUE (t1.normalize() == Tuple::Vector(1, 0, 0));
    Tuple t2 = Tuple::Vector(1, 2, 3);
    Tuple t2n = t2.normalize();
    EXPECT_TRUE(t2n == Tuple::Vector(0.26726, 0.53452, 0.80178));
    EXPECT_DOUBLE_EQ(t2n.Magnitude(), 1.0);

}

TEST(TupleTest, dot) {
    Tuple t1 = Tuple::Vector(1, 2, 3);
    Tuple t2 = Tuple::Vector(2, 3, 4);
    EXPECT_DOUBLE_EQ(t1.Dot(t2), 20);
}

TEST(TupleTest, cross) {
    Tuple t1 = Tuple::Vector(1, 2, 3);
    Tuple t2 = Tuple::Vector(2, 3, 4);
    EXPECT_TRUE (t1.Cross(t2) == Tuple::Vector(-1, 2, -1));
    EXPECT_TRUE (t2.Cross(t1) == Tuple::Vector(1, -2, 1));
}