#ifndef INCLUDE_LINALG_VECTOR_H_
#define INCLUDE_LINALG_VECTOR_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace linalg {
class Vector2D {
 public:
  Vector2D(double x, double y) : x_(x), y_(y) {}

  Vector2D operator+(const Vector2D &other) const;
  Vector2D operator-(const Vector2D &other) const;
  Vector2D &operator+=(const Vector2D &other);
  Vector2D &operator-=(const Vector2D &other);

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
