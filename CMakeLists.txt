cmake_minimum_required(VERSION 3.31)
project(equation_generator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
pybind11
GIT_REPOSITORY https://github.com/pybind/pybind11.git
GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(pybind11)

add_library(equation_generator STATIC
src/nodes/ValueNode.cpp
src/nodes/operations/AddNode.cpp
src/nodes/operations/MultNode.cpp
src/generator/Generator.cpp
src/generator/operators/NodeGenerator.cpp
src/generator/random.cpp
src/generator/operators/NodeOptimizer.cpp
src/generator/operators/NodeFlattener.cpp
src/generator/inspectors/EquationScorer.cpp
)

pybind11_add_module(equation_generator_python
bindings/python/module.cpp
)

target_link_libraries(equation_generator_python
PRIVATE equation_generator
)

add_subdirectory(tests)
