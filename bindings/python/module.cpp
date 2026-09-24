#include <pybind11/pybind11.h>

void bind_settings(pybind11::module_& m);
void bind_generator(pybind11::module_& m);

PYBIND11_MODULE(eqgen, m)
{
  m.doc() = "Equation generator Python bindings";

  bind_settings(m);
  bind_generator(m);
}
