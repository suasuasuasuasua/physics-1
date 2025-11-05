#include "example/functions.h"

#include <csignal>
#include <stdexcept>

namespace example::functions {
double add(double i, double j) { return i + j; }
double sub(double i, double j) { return i - j; }
double mul(double i, double j) { return i * j; }
double div(double i, double j) {
  if (j == 0.0) {
    throw std::invalid_argument("Divisor is zero");
  }
  return i / j;
}
}  // namespace example::functions
