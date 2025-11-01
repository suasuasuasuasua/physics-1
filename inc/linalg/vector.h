#ifndef INCLUDE_LINALG_VECTOR_H_
#define INCLUDE_LINALG_VECTOR_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace linalg {
class Vector2 {
 public:
  Vector2(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}

  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator-(const Vector2 &other) const;
  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);

  std::string toString();

  [[nodiscard]] double x() const;
  void x(const double &x);
  [[nodiscard]] double y() const;
  void y(const double &y);

 private:
  double x_{}, y_{};
};

void init_linalg(py::module_ &m);
}  // namespace linalg
#endif  // INCLUDE_LINALG_VECTOR_H_
