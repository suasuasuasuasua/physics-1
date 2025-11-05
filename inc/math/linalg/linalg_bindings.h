#ifndef INCLUDE_LINALG_LINALG_BINDINGS_H_
#define INCLUDE_LINALG_LINALG_BINDINGS_H_

#include <math/linalg/vector.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace math::linalg {
void init_linalg(py::module_ &m);
}  // namespace math::linalg

#endif  // INCLUDE_LINALG_LINALG_BINDINGS_H_
