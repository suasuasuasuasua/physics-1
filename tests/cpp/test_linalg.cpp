#include <gtest/gtest.h>
#include <math/linalg/vector.h>

#include <cmath>
#include <stdexcept>

#include "math/constants.h"

namespace {
TEST(Vector2Test, Add) {
  math::linalg::Vector2 v1(1.0, 2.0);
  math::linalg::Vector2 v2(3.0, 4.0);

  math::linalg::Vector2 v3 = v1 + v2;

  EXPECT_EQ(v3.x(), 4.0);
  EXPECT_EQ(v3.y(), 6.0);
}
TEST(Vector2Test, AddSelf) {
  math::linalg::Vector2 v1(1.0, 2.0);
  math::linalg::Vector2 v2(3.0, 4.0);

  v1 += v2;

  EXPECT_EQ(v1.x(), 4.0);
  EXPECT_EQ(v1.y(), 6.0);
}
TEST(Vector2Test, Sub) {
  math::linalg::Vector2 v1(1.0, 2.0);
  math::linalg::Vector2 v2(3.0, 4.0);

  math::linalg::Vector2 v3 = v1 - v2;

  EXPECT_EQ(v3.x(), -2.0);
  EXPECT_EQ(v3.y(), -2.0);
}
TEST(Vector2Test, SubSelf) {
  math::linalg::Vector2 v1(1.0, 2.0);
  math::linalg::Vector2 v2(3.0, 4.0);

  v1 -= v2;

  EXPECT_EQ(v1.x(), -2.0);
  EXPECT_EQ(v1.y(), -2.0);
}
TEST(Vector2Test, Mul) {
  math::linalg::Vector2 v1(1.0, 2.0);
  double scalar = 3.0;

  math::linalg::Vector2 v3 = v1 * scalar;

  EXPECT_EQ(v3.x(), 3.0);
  EXPECT_EQ(v3.y(), 6.0);
}
TEST(Vector2Test, MulSelf) {
  math::linalg::Vector2 v1(1.0, 2.0);
  double scalar = 3.0;

  v1 *= scalar;

  EXPECT_EQ(v1.x(), 3.0);
  EXPECT_EQ(v1.y(), 6.0);
}
TEST(Vector2Test, Div) {
  math::linalg::Vector2 v1(3.0, 6.0);
  double scalar = 3.0;

  math::linalg::Vector2 v3 = v1 / scalar;

  EXPECT_EQ(v3.x(), 1.0);
  EXPECT_EQ(v3.y(), 2.0);
}
TEST(Vector2Test, DivSelf) {
  math::linalg::Vector2 v1(3.0, 6.0);
  double scalar = 3.0;

  v1 /= scalar;

  EXPECT_EQ(v1.x(), 1.0);
  EXPECT_EQ(v1.y(), 2.0);
}
TEST(Vector2Test, DivZero) {
  math::linalg::Vector2 v1(3.0, 6.0);
  double scalar = 0.0;

  EXPECT_THROW(v1 / scalar, std::invalid_argument);

  math::linalg::Vector2 v2 = scalar / v1;
  EXPECT_EQ(v2.x(), 0);
  EXPECT_EQ(v2.y(), 0);
}
TEST(Vector2Test, Equal) {
  math::linalg::Vector2 v1(3.0, 6.0);
  math::linalg::Vector2 v2(3.0, 6.0);

  EXPECT_TRUE(v1 == v2);
}
TEST(Vector2Test, NotEqual) {
  math::linalg::Vector2 v1(3.0, 6.0);
  math::linalg::Vector2 v2(5.0, 7.0);

  EXPECT_TRUE(v1 != v2);
}
TEST(Vector2Test, Mag) {
  math::linalg::Vector2 v1(12, 34);
  double magnitude = 1300;

  EXPECT_EQ(v1.mag(), magnitude);
}
TEST(Vector2Test, Unit) {
  math::linalg::Vector2 v1(12, 34);
  math::linalg::Vector2 v2 = v1.unit();
  double magnitude = 1300;

  EXPECT_EQ(v2.x(), v1.x() / magnitude);
  EXPECT_EQ(v2.y(), v1.y() / magnitude);
}
TEST(Vector2Test, Angle) {
  math::linalg::Vector2 v1(-2, 3);
  double ang = math::constants::deg_to_rad(124);

  // pretty bad estimate from the video of 124 degrees!
  EXPECT_NEAR(v1.angle(), ang, 0.01);
}
TEST(Vector2Test, FromMagAng) {
  double magnitude = 2;
  double angle = math::constants::deg_to_rad(30);

  math::linalg::Vector2 v1 =
      math::linalg::Vector2::from_mag_ang(magnitude, angle);
  EXPECT_NEAR(v1.x(), std::sqrt(3), 0.001);
  EXPECT_NEAR(v1.y(), 1.0, 0.001);
}
TEST(Vector2Test, String) {
  math::linalg::Vector2 v1(1.1, 2.2);
  std::string repr("X: 1.1 Y: 2.2");

  EXPECT_EQ(v1.to_string(), repr);
}
}  // namespace
