cmake_minimum_required(VERSION 3.31)
project(equation_generator_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp
        tools/EquationVerifier.cpp
        ../src/nodes/ValueNode.cpp
        ../src/nodes/operations/AddNode.cpp
        ../src/nodes/operations/MultNode.cpp
        ../src/generator/Generator.cpp
        ../src/generator/GeneratorImpl.cpp
        ../src/generator/Random.cpp
        ../src/generator/operators/NodeGenerator.cpp
        ../src/generator/operators/NodeOptimizer.cpp
        ../src/generator/operators/NodeFlattener.cpp
        ../src/generator/inspectors/EquationScorer.cpp
)

target_include_directories(test PRIVATE
        ${PROJECT_SOURCE_DIR}/../include
)
