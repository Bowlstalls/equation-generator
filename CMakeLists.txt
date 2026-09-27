cmake_minimum_required(VERSION 3.31)

project(equation_generator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PYTHON "Build Python bindings" ON)
option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

message(STATUS "BUILD_PYTHON = ${BUILD_PYTHON}")
if(BUILD_PYTHON)
add_subdirectory(bindings/python)
endif()

if(BUILD_TESTS)
add_subdirectory(tests)
endif()
