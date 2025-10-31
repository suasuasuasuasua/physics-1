#include <numeric>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

#include "physics/kinematics/motion.h"

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

  // Kinematics submodule
  auto kinematics = m.def_submodule("kinematics", "Kinematics equations for motion");
  
  kinematics.def("position", &physics::kinematics::position,
      py::arg("x0"), py::arg("v0"), py::arg("t"), py::arg("a"),
      R"pbdoc(
          Calculate position with constant acceleration.
          
          Equation: x = x0 + v0*t + 0.5*a*t^2
          
          Parameters
          ----------
          x0 : float
              Initial position (m)
          v0 : float
              Initial velocity (m/s)
          t : float
              Time elapsed (s)
          a : float
              Acceleration (m/s^2)
              
          Returns
          -------
          float
              Position at time t (m)
      )pbdoc");
  
  kinematics.def("velocity_at_time", &physics::kinematics::velocity_at_time,
      py::arg("v0"), py::arg("t"), py::arg("a"),
      R"pbdoc(
          Calculate velocity at a given time with constant acceleration.
          
          Equation: v = v0 + a*t
          
          Parameters
          ----------
          v0 : float
              Initial velocity (m/s)
          t : float
              Time elapsed (s)
          a : float
              Acceleration (m/s^2)
              
          Returns
          -------
          float
              Velocity at time t (m/s)
      )pbdoc");
  
  kinematics.def("velocity_from_position", &physics::kinematics::velocity_from_position,
      py::arg("v0"), py::arg("x"), py::arg("x0"), py::arg("a"),
      R"pbdoc(
          Calculate velocity from position using kinematics.
          
          Equation: v^2 = v0^2 + 2*a*(x - x0)
          
          Parameters
          ----------
          v0 : float
              Initial velocity (m/s)
          x : float
              Final position (m)
          x0 : float
              Initial position (m)
          a : float
              Acceleration (m/s^2)
              
          Returns
          -------
          float
              Velocity at position x (m/s)
      )pbdoc");
  
  kinematics.def("time_to_position", &physics::kinematics::time_to_position,
      py::arg("x0"), py::arg("x"), py::arg("v0"), py::arg("a"),
      R"pbdoc(
          Calculate time to reach a given position with constant acceleration.
          
          Solves: x = x0 + v0*t + 0.5*a*t^2 for t
          
          Parameters
          ----------
          x0 : float
              Initial position (m)
          x : float
              Final position (m)
          v0 : float
              Initial velocity (m/s)
          a : float
              Acceleration (m/s^2)
              
          Returns
          -------
          float
              Time to reach position x (s)
      )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
