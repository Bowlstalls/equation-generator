add_library(equation_generator SHARED
        nodes/ValueNode.cpp
        nodes/operations/AddNode.cpp
        nodes/operations/MultNode.cpp
        generator/Generator.cpp
        generator/GeneratorImpl.cpp
        generator/Random.cpp
        generator/operators/NodeGenerator.cpp
        generator/operators/NodeOptimizer.cpp
        generator/operators/NodeFlattener.cpp
        generator/inspectors/EquationScorer.cpp
        c/equation_generator.cpp
        c/converters.cpp
)

target_include_directories(equation_generator PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(equation_generator PRIVATE
        EQUATION_GENERATOR_BUILD
)
