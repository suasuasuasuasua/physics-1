#ifndef INCLUDE_EXAMPLE_BINDINGS_H_
#define INCLUDE_EXAMPLE_BINDINGS_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace example::functions {
void init_functions(py::module_ &m);
}  // namespace example::functions

#endif  // INCLUDE_EXAMPLE_BINDINGS_H_
