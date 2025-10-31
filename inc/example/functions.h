#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_example(py::module_ &m);
namespace example {
int add(int i, int j);
int sub(int i, int j);
double mul(double i, double j);
double div(double i, double j);
void init_example(py::module_ &m);
} // namespace example
