#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(equation_generator, m)
{
  m.doc() = "Equation generator Python bindings";
}
