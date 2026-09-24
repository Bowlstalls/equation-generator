#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <equation-generator/Generator.h>

void bind_equation(pybind11::module_& m)
{
  pybind11::class_<equation_generator::Equation>(m, "Equation")
    .def(pybind11::init<>())
    .def_readonly("str", &equation_generator::Equation::str)
    .def_readonly("roots", &equation_generator::Equation::roots)
    .def_readonly("score", &equation_generator::Equation::score);
}
