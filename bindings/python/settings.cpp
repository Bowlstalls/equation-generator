#include <pybind11/pybind11.h>
#include <equation-generator/Settings.h>

void bind_value_settings(pybind11::module_& m)
{
  auto value_settings = pybind11::class_<equation_generator::ValueSettings>(m, "ValueSettings");

  pybind11::class_<equation_generator::ValueSettings::Item>(value_settings, "Item")
    .def(pybind11::init<>())
    .def_readwrite("max", &equation_generator::ValueSettings::Item::max)
    .def_readwrite("lowBias", &equation_generator::ValueSettings::Item::lowBias)
    .def_readwrite("negativeChance", &equation_generator::ValueSettings::Item::negativeChance);

  value_settings
    .def(pybind11::init<>())
    .def_readwrite("base", &equation_generator::ValueSettings::base)
    .def_readwrite("values", &equation_generator::ValueSettings::values)
    .def_readwrite("roots", &equation_generator::ValueSettings::roots)
    .def_readwrite("powers", &equation_generator::ValueSettings::powers);
}

void bind_structure_settings(pybind11::module_& m)
{
  auto structure_settings = pybind11::class_<equation_generator::StructureSettings>(m, "StructureSettings");

  pybind11::class_<equation_generator::StructureSettings::OperationWeights>(structure_settings, "OperationWeights")
    .def(pybind11::init<>())
    .def_readwrite("add", &equation_generator::StructureSettings::OperationWeights::add)
    .def_readwrite("mult", &equation_generator::StructureSettings::OperationWeights::mult);

  structure_settings
    .def(pybind11::init<>())
    .def_readwrite("maxDepth", &equation_generator::StructureSettings::maxDepth)
    .def_readwrite("maxWidth", &equation_generator::StructureSettings::maxWidth)
    .def_readwrite("valueChance", &equation_generator::StructureSettings::valueChance)
    .def_readwrite("rightSideChance", &equation_generator::StructureSettings::rightSideChance)
    .def_readwrite("operationWeights", &equation_generator::StructureSettings::operationWeights);
}

void bind_settings(pybind11::module_& m)
{
  bind_value_settings(m);
  bind_structure_settings(m);

  pybind11::class_<equation_generator::Settings>(m, "Settings")
    .def(pybind11::init<>())
    .def_readwrite("seed", &equation_generator::Settings::seed)
    .def_readwrite("variableName", &equation_generator::Settings::variableName)
    .def_readwrite("degree", &equation_generator::Settings::degree)
    .def_readwrite("valueSettings", &equation_generator::Settings::valueSettings)
    .def_readwrite("structureSettings", &equation_generator::Settings::structureSettings);
}
