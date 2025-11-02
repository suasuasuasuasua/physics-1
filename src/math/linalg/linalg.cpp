#include <math/linalg/linalg_bindings.h>
#include <math/linalg/vector.h>

#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace math::linalg {
void init_linalg(py::module_ &m) {
  auto linalg = m.def_submodule("linalg", "A general linear algebra library");

  py::class_<Vector2>(linalg, "Vector2")
      .def(py::init<double, double>(), py::arg("x") = 0.0, py::arg("y") = 0.0)
      // members
      .def("x", py::overload_cast<>(&Vector2::x, py::const_))
      .def("x", py::overload_cast<const double &>(&Vector2::x), py::arg("x"))
      .def("y", py::overload_cast<>(&Vector2::y, py::const_))
      .def("y", py::overload_cast<const double &>(&Vector2::y), py::arg("y"))
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
