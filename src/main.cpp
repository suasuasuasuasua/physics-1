#include <numeric>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) { return i + j; }
int sub(int i, int j) { return i - j; }

namespace py = pybind11;

PYBIND11_MODULE(_core, m, py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil()) {
  m.doc() = R"pbdoc(
        Physics 1 Module
        -----------------------

        .. currentmodule:: physics_1

        .. autosummary::
           :toctree: _generate

           add
           subtract
           multiply
    )pbdoc";

  m.def("add", &add, R"pbdoc(
        Add two numbers
    )pbdoc");

  m.def("sub", &sub, R"pbdoc(
        Subtract two numbers
    )pbdoc");

  m.def(
      "reduce",
      [](const std::vector<double> &v, double initial = 0.0) {
        return std::reduce(v.begin(), v.end(), initial);
      },
      R"pbdoc(
        Reduce the number in a list
      )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
