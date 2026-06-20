cmake_minimum_required(VERSION 3.31)
project(equation_generator)

set(CMAKE_CXX_STANDARD 20)

add_library(equation_generator STATIC library.cpp
        src/nodes/Node.h
        src/nodes/ValueNode.h
        src/nodes/VarNode.h
        src/nodes/AddNode.h
        src/nodes/MultNode.h
        src/nodes/ValueNode.cpp
        src/nodes/VarNode.cpp
        src/nodes/AddNode.cpp
        src/nodes/MultNode.cpp)
