cmake_minimum_required(VERSION 3.31)
project(equation_generator_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp
        tools/EquationVerifier.h)
target_link_libraries(test PRIVATE equation_generator)