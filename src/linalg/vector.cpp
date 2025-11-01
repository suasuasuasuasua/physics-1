#include <linalg/vector.h>
#include <pybind11/detail/common.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>

namespace py = pybind11;

namespace linalg {
Vector2 Vector2::operator+(const Vector2 &other) const {
  return Vector2{x_ + other.x_, y_ + other.y_};
}
Vector2 Vector2::operator-(const Vector2 &other) const {
  return Vector2{x_ - other.x_, y_ - other.y_};
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

double Vector2::x() const { return x_; }
void Vector2::x(const double &x) { x_ = std::move(x_); }
double Vector2::y() const { return y_; }
void Vector2::y(const double &y) { y_ = std::move(y_); }

std::string Vector2::toString() {
  std::stringstream ss;
  ss << "X: " << x_ << " " << " Y: " << y_;
  return ss.str();
}

void init_linalg(py::module_ &m) {
  auto linalg = m.def_submodule("linalg", "A general linear algebra library");

  py::class_<Vector2>(linalg, "Vector2")
      .def(py::init<double, double>(), py::arg("x") = 0.0, py::arg("y") = 0.0)
      // members
      .def("x", py::overload_cast<>(&Vector2::x, py::const_))
      .def("x", py::overload_cast<const double &>(&Vector2::x), py::arg("x"))
      .def("y", py::overload_cast<>(&Vector2::y, py::const_))
      .def("y", py::overload_cast<const double &>(&Vector2::x), py::arg("y"))
      // overloads
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self += py::self)
      .def(py::self -= py::self)
      .def("__repr__", &Vector2::toString);
}
}  // namespace linalg
