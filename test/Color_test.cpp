#include <gtest/gtest.h>
#include <Color.h>

TEST(ColorTest, initilize) {
    Color c(-0.5, 0.4, 1.7);
    EXPECT_DOUBLE_EQ(c.Red(), -0.5);
    EXPECT_DOUBLE_EQ(c.Green(), 0.4);
    EXPECT_DOUBLE_EQ(c.Blue(), 1.7);
}

TEST(ColorTest, Operator) {
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);

    EXPECT_TRUE(c1 + c2 == Color(1.6, 0.7, 1.0));
    EXPECT_TRUE(c1 - c2 == Color(0.2, 0.5, 0.5));
    EXPECT_TRUE(c1 *2 == Color(1.8, 1.2, 1.5));
    EXPECT_TRUE(c1.HadamardProduct(c2) == Color(0.63, 0.06, 0.1875));
}