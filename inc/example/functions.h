#ifndef INCLUDE_EXAMPLE_FUNCTIONS_H_
#define INCLUDE_EXAMPLE_FUNCTIONS_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_example(py::module_ &m);
namespace example {
int add(int i, int j);
int sub(int i, int j);
double mul(double i, double j);
double div(double i, double j);

void init_example(py::module_ &m);
}  // namespace example

#endif  // INCLUDE_EXAMPLE_FUNCTIONS_H_
