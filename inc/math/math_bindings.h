#ifndef INCLUDE_MATH_MATH_BINDINGS_H_
#define INCLUDE_MATH_MATH_BINDINGS_H_

#include <math/linalg/vector.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace math {
void init_math(py::module_ &m);
}  // namespace math

#endif  // INCLUDE_MATH_MATH_BINDINGS_H_
