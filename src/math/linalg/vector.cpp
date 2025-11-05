#include <math/linalg/vector.h>

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace math::linalg {
Vector2 Vector2::operator+(const Vector2 &other) const {
  return {x_ + other.x_, y_ + other.y_};
}
Vector2 Vector2::operator-(const Vector2 &other) const {
  return {x_ - other.x_, y_ - other.y_};
}
Vector2 Vector2::operator*(double scalar) const {
  return {x_ * scalar, y_ * scalar};
}
Vector2 Vector2::operator/(double scalar) const {
  if (scalar == 0.0) {
    throw std::invalid_argument("Vector divison must not be by zero");
  }
  return {x_ / scalar, y_ / scalar};
}
Vector2 &Vector2::operator+=(const Vector2 &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}
Vector2 &Vector2::operator-=(const Vector2 &other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}
Vector2 &Vector2::operator*=(double scalar) {
  x_ *= scalar;
  y_ *= scalar;
  return *this;
}
Vector2 &Vector2::operator/=(double scalar) {
  if (scalar == 0.0) {
    throw std::invalid_argument("Vector divison must not be by zero");
  }
  x_ /= scalar;
  y_ /= scalar;
  return *this;
}
Vector2 Vector2::operator-() const { return {-x_, -y_}; }
bool operator==(const Vector2 &lhs, const Vector2 &rhs) {
  return (lhs.x_ == rhs.x_) and (lhs.y_ == rhs.y_);
}
bool operator!=(const Vector2 &lhs, const Vector2 &rhs) {
  return (lhs.x_ != rhs.x_) or (lhs.y_ != rhs.y_);
}
Vector2 operator*(double scalar, const Vector2 &v) {
  return {scalar * v.x(), scalar * v.y()};
}
Vector2 operator/(double scalar, const Vector2 &v) {
  return {scalar / v.x(), scalar / v.y()};
}

double Vector2::x() const { return x_; }
void Vector2::x(const double &x) { x_ = std::move(x); }
double Vector2::y() const { return y_; }
void Vector2::y(const double &y) { y_ = std::move(y); }

std::string Vector2::to_string() {
  std::stringstream ss;
  ss << "X: " << x_ << " Y: " << y_;
  return ss.str();
}

double Vector2::mag() const {
  double magnitude = x_ * x_ + y_ * y_;
  return magnitude;
}
Vector2 Vector2::unit() const {
  double magnitude = mag();
  return *this / magnitude;
}
double Vector2::angle() const {
  double ang = std::atan2(y_, x_);
  return ang;
}
Vector2 Vector2::from_mag_ang(double magnitude, double angle) {
  double x = magnitude * std::cos(angle);
  double y = magnitude * std::sin(angle);
  return {x, y};
}
}  // namespace math::linalg
