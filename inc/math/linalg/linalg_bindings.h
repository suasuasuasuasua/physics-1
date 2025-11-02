#ifndef INCLUDE_LINALG_BINDINGS_H_
#define INCLUDE_LINALG_BINDINGS_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace math::linalg {
void init_linalg(py::module_ &m);
}  // namespace math::linalg

#endif  // INCLUDE_LINALG_BINDINGS_H_
