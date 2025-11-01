#include <example/functions.h>
#include <gtest/gtest.h>

namespace {
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(FunctionTest, Add) {
  EXPECT_EQ(example::add(10, 4), 14);
  EXPECT_EQ(example::add(1234, 412341234), 412342468);
}

TEST(FunctionTest, Sub) {
  EXPECT_EQ(example::sub(10, 4), 6);
  EXPECT_EQ(example::sub(1234, 412341234), -412340000);
}

TEST(FunctionTest, Mul) {
  EXPECT_EQ(example::mul(10, 4), 40);
  EXPECT_EQ(example::mul(123, 456), 56088);
}
}  // namespace
