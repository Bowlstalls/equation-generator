include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(eqgen
        module.cpp
        settings.cpp
        generator.cpp
        equation.cpp
)
target_link_libraries(eqgen PRIVATE
        equation_generator
)
