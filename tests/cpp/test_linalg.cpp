#include <gtest/gtest.h>
#include <linalg/vector.h>

namespace {
TEST(Vector2Test, Add) {
  linalg::Vector2 v1(1.0, 2.0);
  linalg::Vector2 v2(3.0, 4.0);

  linalg::Vector2 v3 = v1 + v2;

  EXPECT_EQ(v3.x(), 4.0);
  EXPECT_EQ(v3.y(), 6.0);
}
TEST(Vector2Test, AddSelf) {
  linalg::Vector2 v1(1.0, 2.0);
  linalg::Vector2 v2(3.0, 4.0);

  v1 += v2;

  EXPECT_EQ(v1.x(), 4.0);
  EXPECT_EQ(v1.y(), 6.0);
}
TEST(Vector2Test, Sub) {
  linalg::Vector2 v1(1.0, 2.0);
  linalg::Vector2 v2(3.0, 4.0);

  linalg::Vector2 v3 = v1 - v2;

  EXPECT_EQ(v3.x(), -2.0);
  EXPECT_EQ(v3.y(), -2.0);
}
TEST(Vector2Test, SubSelf) {
  linalg::Vector2 v1(1.0, 2.0);
  linalg::Vector2 v2(3.0, 4.0);

  v1 -= v2;

  EXPECT_EQ(v1.x(), -2.0);
  EXPECT_EQ(v1.y(), -2.0);
}
TEST(Vector2Test, Mul) {
  linalg::Vector2 v1(1.0, 2.0);
  double scalar = 3.0;

  linalg::Vector2 v3 = v1 * scalar;

  EXPECT_EQ(v3.x(), 3.0);
  EXPECT_EQ(v3.y(), 6.0);
}
TEST(Vector2Test, MulSelf) {
  linalg::Vector2 v1(1.0, 2.0);
  double scalar = 3.0;

  v1 *= scalar;

  EXPECT_EQ(v1.x(), 3.0);
  EXPECT_EQ(v1.y(), 6.0);
}
TEST(Vector2Test, String) {
  linalg::Vector2 v1(1.1, 2.2);
  std::string repr("X: 1.1 Y: 2.2");

  EXPECT_EQ(v1.toString(), repr);
}
}  // namespace
