#include <pybind11/pybind11.h>
#include <equation-generator/Generator.h>

void bind_generator(pybind11::module_& m)
{
  pybind11::class_<equation_generator::Generator>(m, "Generator")
    .def(pybind11::init<const equation_generator::Settings&>())
    .def("generate", &equation_generator::Generator::generate);
}
