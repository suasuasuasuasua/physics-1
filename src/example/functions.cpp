#include "example/functions.h"

#include <pybind11/pybind11.h>

#include <csignal>
#include <exception>
#include <stdexcept>

namespace py = pybind11;

namespace example {
int add(int i, int j) { return i + j; }
int sub(int i, int j) { return i - j; }
double mul(double i, double j) { return i * j; }
double div(double i, double j) {
  if (j == 0.0) {
    throw std::invalid_argument("Divisor is zero");
  }
  return i / j;
}

void init_example(py::module_ &m) {
  m.def_submodule("example", "Some example functions demoing pybind11")
      .def("add", &example::add, py::arg("i"), py::arg("j"), R"pbdoc(
        Add two numbers
      )pbdoc")
      .def("sub", &example::sub, py::arg("i"), py::arg("j"), R"pbdoc(
        Subtract two numbers
      )pbdoc")
      .def("mul", &example::sub, py::arg("i"), py::arg("j"), R"pbdoc(
      )pbdoc");
}
}  // namespace example
