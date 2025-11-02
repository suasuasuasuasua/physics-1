#ifndef INCLUDE_LINALG_VECTOR_H_
#define INCLUDE_LINALG_VECTOR_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace math::linalg {
class Vector2 {
 public:
  Vector2(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}

  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator-(const Vector2 &other) const;
  Vector2 operator*(double scalar) const;
  Vector2 operator/(double scalar) const;
  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator*=(double scalar);
  Vector2 &operator/=(double scalar);
  friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
  friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
  friend Vector2 operator*(double f, const Vector2 &v);
  friend Vector2 operator/(double f, const Vector2 &v);

  std::string to_string();

  [[nodiscard]] double x() const;
  void x(const double &x);
  [[nodiscard]] double y() const;
  void y(const double &y);

  [[nodiscard]] double mag() const;
  [[nodiscard]] Vector2 unit() const;
  [[nodiscard]] double angle() const;
  static Vector2 from_mag_ang(double magnitude, double angle);

 private:
  double x_{}, y_{};
};

Vector2 operator*(double f, const Vector2 &v);
Vector2 operator/(double f, const Vector2 &v);
bool operator==(const Vector2 &lhs, const Vector2 &rhs);
bool operator!=(const Vector2 &lhs, const Vector2 &rhs);

void init_linalg(py::module_ &m);
}  // namespace math::linalg

#endif  // INCLUDE_LINALG_VECTOR_H_
