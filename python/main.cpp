#include <example/functions.h>
#include <math/constants.h>
#include <math/linalg/vector.h>
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

  // Create package hierarchy in C++
  
  // Create example package and functions submodule
  auto example_pkg = m.def_submodule("example", "Example package with demonstration functions");
  auto functions_module = example_pkg.def_submodule("functions", "Functions module with basic mathematical operations");
  example::functions::init_functions(functions_module);
  
  // Create math package
  auto math_pkg = m.def_submodule("math", "Math package with mathematical utilities and constants");
  
  // Create math.constants submodule
  auto constants_module = math_pkg.def_submodule("constants", "Mathematical constants and conversion functions");
  constants_module.attr("PI") = M_PI;
  constants_module.attr("E") = M_E;
  constants_module.def("deg_to_rad", &math::constants::deg_to_rad, py::arg("ang"),
                       "Convert degrees to radians");
  
  // Create math.linalg package and vector submodule
  auto linalg_pkg = math_pkg.def_submodule("linalg", "Linear algebra package with vector operations");
  auto vector_module = linalg_pkg.def_submodule("vector", "Vector module with Vector2 class for 2D vector operations");
  math::linalg::init_linalg(vector_module);

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
