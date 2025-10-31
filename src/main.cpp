#include <example/functions.h>
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_core, m, py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil()) {
  m.doc() = R"pbdoc(
        Physics 1 Module
        -----------------------

        .. currentmodule:: physics_1

        .. autosummary::
           :toctree: _generate
    )pbdoc";

  example::init_example(m);

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
