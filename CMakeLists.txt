cmake_minimum_required(VERSION 3.31)
project(equation_generator)

set(CMAKE_CXX_STANDARD 20)

add_library(equation_generator STATIC
        src/nodes/Node.h
        src/nodes/ValueNode.h
        src/nodes/operations/AddNode.h
        src/nodes/operations/MultNode.h
        src/nodes/ValueNode.cpp
        src/nodes/operations/AddNode.cpp
        src/nodes/operations/MultNode.cpp
        src/Equation.cpp
        src/Equation.h
        src/generator/Generator.cpp
        src/generator/Generator.h
        src/Equation.cpp
        src/nodes/operations/OperationNode.cpp
        src/nodes/operations/OperationNode.h
        src/generator/operators/NodeGenerator.cpp
        src/generator/operators/NodeGenerator.h
        src/generator/settings.h
        src/generator/random.h
        src/nodes/NodeType.h
        src/generator/random.cpp
        src/generator/operators/NodeOptimizer.cpp
        src/generator/operators/NodeOptimizer.h
        src/generator/operators/NodeFlattener.cpp
        src/generator/operators/NodeFlattener.h
)

add_subdirectory(tests)
