#include <math/linalg/vector.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace py = pybind11;

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
void Vector2::x(const double &x) { x_ = std::move(x_); }
double Vector2::y() const { return y_; }
void Vector2::y(const double &y) { y_ = std::move(y_); }

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

void init_linalg(py::module_ &m) {
  auto linalg = m.def_submodule("linalg", "A general linear algebra library");

  py::class_<Vector2>(linalg, "Vector2")
      .def(py::init<double, double>(), py::arg("x") = 0.0, py::arg("y") = 0.0)
      // members
      .def_property("x", py::overload_cast<>(&Vector2::x, py::const_),
                    py::overload_cast<const double &>(&Vector2::x))
      .def_property("y", py::overload_cast<>(&Vector2::y, py::const_),
                    py::overload_cast<const double &>(&Vector2::y))
      // overloads
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self - py::self)
      .def(py::self -= py::self)
      .def(py::self * float())
      .def(py::self *= float())
      .def(float() * py::self)
      .def(py::self / float())
      .def(py::self /= float())
      .def(float() / py::self)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(-py::self)
      // methods
      .def("mag", py::overload_cast<>(&Vector2::mag, py::const_))
      .def("unit", py::overload_cast<>(&Vector2::unit, py::const_))
      .def("angle", py::overload_cast<>(&Vector2::angle, py::const_))
      .def_static("from_mag_ang",
                  py::overload_cast<double, double>(&Vector2::from_mag_ang))
      .def("__repr__", &Vector2::to_string);
}
}  // namespace math::linalg
