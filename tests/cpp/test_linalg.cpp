#include <gtest/gtest.h>
#include <linalg/vector.h>

TEST(LinalgTest, Vector2DBasicTest) {
  linalg::Vector2D v1(1.0, 2.0);
  linalg::Vector2D v2(3.0, 4.0);
  
  linalg::Vector2D v3 = v1 + v2;
  
  EXPECT_EQ(v3.x(), 4.0);
  EXPECT_EQ(v3.y(), 6.0);
}
