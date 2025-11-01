#include <gtest/gtest.h>
#include <linalg/vector.h>

#include <cmath>
#include <stdexcept>

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
TEST(Vector2Test, Div) {
  linalg::Vector2 v1(3.0, 6.0);
  double scalar = 3.0;

  linalg::Vector2 v3 = v1 / scalar;

  EXPECT_EQ(v3.x(), 1.0);
  EXPECT_EQ(v3.y(), 2.0);
}
TEST(Vector2Test, DivSelf) {
  linalg::Vector2 v1(3.0, 6.0);
  double scalar = 3.0;

  v1 /= scalar;

  EXPECT_EQ(v1.x(), 1.0);
  EXPECT_EQ(v1.y(), 2.0);
}
TEST(Vector2Test, DivZero) {
  linalg::Vector2 v1(3.0, 6.0);
  double scalar = 0.0;

  EXPECT_THROW(v1 / scalar, std::invalid_argument);

  linalg::Vector2 v2 = scalar / v1;
  EXPECT_EQ(v2.x(), 0);
  EXPECT_EQ(v2.y(), 0);
}
TEST(Vector2Test, Mag) {
  linalg::Vector2 v1(12, 34);
  double magnitude = 1300;

  EXPECT_EQ(v1.mag(), magnitude);
}
TEST(Vector2Test, Unit) {
  linalg::Vector2 v1(12, 34);
  linalg::Vector2 v2 = v1.unit();
  double magnitude = 1300;

  EXPECT_EQ(v2.x(), v1.x() / magnitude);
  EXPECT_EQ(v2.y(), v1.y() / magnitude);
}
TEST(Vector2Test, Angle) {
  linalg::Vector2 v1(-2, 3);
  double ang = 124 * (M_PI / 180.0);

  // pretty bad estimate from the video of 124 degrees!
  EXPECT_NEAR(v1.angle(), ang, 0.01);
}
TEST(Vector2Test, String) {
  linalg::Vector2 v1(1.1, 2.2);
  std::string repr("X: 1.1 Y: 2.2");

  EXPECT_EQ(v1.to_string(), repr);
}
}  // namespace
