#include <gtest/gtest.h>
#include <Tuple.h>

// Demonstrate some basic assertions.
TEST(TupleTest, TupleIsPoint) {
  Tuple t(4.3, -4.2, 3.1, 1.0);
   EXPECT_EQ(t.IsPoint(), true);
}

TEST(TupleTest, TupleIsVector) {
  Tuple t(4.3, -4.2, 3.1, 0.0);
   EXPECT_EQ(t.IsVector(), true);
}