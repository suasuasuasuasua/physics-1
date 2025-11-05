#ifndef INCLUDE_EXAMPLE_FUNCTIONS_H_
#define INCLUDE_EXAMPLE_FUNCTIONS_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace example::functions {
double add(double i, double j);
double sub(double i, double j);
double mul(double i, double j);
double div(double i, double j);
}  // namespace example::functions

#endif  // INCLUDE_EXAMPLE_FUNCTIONS_H_
