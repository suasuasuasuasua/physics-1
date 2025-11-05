#include "example/functions.h"

#include <pybind11/pybind11.h>

#include <csignal>
#include <stdexcept>

namespace py = pybind11;

namespace example::functions {
int add(int i, int j) { return i + j; }
int sub(int i, int j) { return i - j; }
double mul(double i, double j) { return i * j; }
double div(double i, double j) {
  if (j == 0.0) {
    throw std::invalid_argument("Divisor is zero");
  }
  return i / j;
}

void init_functions(py::module_ &m) {
  m.def_submodule("functions", "Some example functions demoing pybind11")
      .def("add", &example::functions::add, py::arg("i"), py::arg("j"), R"pbdoc(
        Add two numbers
      )pbdoc")
      .def("sub", &example::functions::sub, py::arg("i"), py::arg("j"), R"pbdoc(
        Subtract two numbers
      )pbdoc")
      .def("mul", &example::functions::sub, py::arg("i"), py::arg("j"), R"pbdoc(
        Multiply two numbers
      )pbdoc");
}
}  // namespace example::functions
