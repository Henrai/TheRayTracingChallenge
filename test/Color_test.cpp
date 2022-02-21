#include <gtest/gtest.h>
#include <Color.h>

TEST(ColorTest, initilize) {
    Color c(-0.5f, 0.4f, 1.7f);
    EXPECT_FLOAT_EQ(c.R(), -0.5f);
    EXPECT_FLOAT_EQ(c.G(), 0.4f);
    EXPECT_FLOAT_EQ(c.B(), 1.7f);
}

TEST(ColorTest, Operator) {
    Color c1(0.9f, 0.6f, 0.75f);
    Color c2(0.7f, 0.1f, 0.25f);

    EXPECT_TRUE(c1 + c2 == Color(1.6f, 0.7f, 1.0f));
    EXPECT_TRUE(c1 - c2 == Color(0.2f, 0.5f, 0.5f));
    EXPECT_TRUE(c1 *2 == Color(1.8, 1.2, 1.5));
    EXPECT_TRUE(c1.HadamardProduct(c2) == Color(0.63f, 0.06f, 0.1875f));
}
