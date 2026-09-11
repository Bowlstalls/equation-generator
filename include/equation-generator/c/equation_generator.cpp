#include "equation_generator.h"

#include <equation-generator/Generator.h>
#include <equation-generator/Settings.h>

#include <cstdlib>
#include <cstring>
#include <new>
#include <string>

namespace {

thread_local std::string last_error;

void set_error(const char *message)
{
    last_error = message;
}

void set_error(const std::exception& e)
{
    last_error = e.what();
}

char *copy_string(const std::string& str)
{
    char *result = static_cast<char *>(std::malloc(str.size() + 1));

    if (!result) {
        return nullptr;
    }

    std::memcpy(result, str.c_str(), str.size() + 1);
    return result;
}

bool convert_settings(
    const eg_settings& input,
    equation_generator::Settings& output)
{
    output.seed = input.seed;

    if (input.variable_name == nullptr) {
        set_error("variable_name cannot be NULL");
        return false;
    }

    output.variableName = input.variable_name;
    output.degree = input.degree;

    output.valueSettings.base = input.value_settings.base;

    output.valueSettings.values.max =
        input.value_settings.values.max;

    output.valueSettings.values.lowBias =
        input.value_settings.values.low_bias;

    output.valueSettings.values.negativeChance =
        input.value_settings.values.negative_chance;

    output.valueSettings.roots.max =
        input.value_settings.roots.max;

    output.valueSettings.roots.lowBias =
        input.value_settings.roots.low_bias;

    output.valueSettings.roots.negativeChance =
        input.value_settings.roots.negative_chance;

    output.valueSettings.powers.max =
        input.value_settings.powers.max;

    output.valueSettings.powers.lowBias =
        input.value_settings.powers.low_bias;

    output.valueSettings.powers.negativeChance =
        input.value_settings.powers.negative_chance;

    output.structureSettings.maxDepth =
        input.structure_settings.max_depth;

    output.structureSettings.maxWidth =
        input.structure_settings.max_width;

    output.structureSettings.valueChance =
        input.structure_settings.value_chance;

    output.structureSettings.rightSideChance =
        input.structure_settings.right_side_chance;

    output.structureSettings.operationWeights[
        equation_generator::Operation::Add
    ] = input.structure_settings.add_weight;

    output.structureSettings.operationWeights[
        equation_generator::Operation::Mult
    ] = input.structure_settings.mult_weight;

    return true;
}

} // namespace


/*
 * This is the actual definition of the opaque C type.
 *
 * C code cannot see this.
 */
struct eg_generator {
    equation_generator::Generator generator;

    explicit eg_generator(
        const equation_generator::Settings& settings)
        : generator(settings)
    {
    }
};


extern "C" {

void eg_settings_default(eg_settings *settings)
{
    if (!settings) {
        return;
    }

    equation_generator::Settings defaults;

    settings->seed = defaults.seed;
    settings->variable_name = "x";
    settings->degree = defaults.degree;

    settings->value_settings.base =
        defaults.valueSettings.base;

    settings->value_settings.values.max =
        defaults.valueSettings.values.max;

    settings->value_settings.values.low_bias =
        defaults.valueSettings.values.lowBias;

    settings->value_settings.values.negative_chance =
        defaults.valueSettings.values.negativeChance;

    settings->value_settings.roots.max =
        defaults.valueSettings.roots.max;

    settings->value_settings.roots.low_bias =
        defaults.valueSettings.roots.lowBias;

    settings->value_settings.roots.negative_chance =
        defaults.valueSettings.roots.negativeChance;

    settings->value_settings.powers.max =
        defaults.valueSettings.powers.max;

    settings->value_settings.powers.low_bias =
        defaults.valueSettings.powers.lowBias;

    settings->value_settings.powers.negative_chance =
        defaults.valueSettings.powers.negativeChance;

    settings->structure_settings.max_depth =
        defaults.structureSettings.maxDepth;

    settings->structure_settings.max_width =
        defaults.structureSettings.maxWidth;

    settings->structure_settings.value_chance =
        defaults.structureSettings.valueChance;

    settings->structure_settings.right_side_chance =
        defaults.structureSettings.rightSideChance;

    settings->structure_settings.add_weight =
        defaults.structureSettings.operationWeights[
            equation_generator::Operation::Add
        ];

    settings->structure_settings.mult_weight =
        defaults.structureSettings.operationWeights[
            equation_generator::Operation::Mult
        ];
}


eg_generator *eg_generator_create(
    const eg_settings *settings)
{
    try {
        equation_generator::Settings cpp_settings;

        if (settings) {
            if (!convert_settings(*settings, cpp_settings)) {
                return nullptr;
            }
        }

        return new eg_generator(cpp_settings);
    }
    catch (const std::exception& e) {
        set_error(e);
        return nullptr;
    }
    catch (...) {
        set_error("Unknown error creating generator");
        return nullptr;
    }
}


void eg_generator_destroy(eg_generator *generator)
{
    delete generator;
}


int eg_generator_generate(
    eg_generator *generator,
    eg_equation *result)
{
    if (!generator) {
        set_error("generator cannot be NULL");
        return 1;
    }

    if (!result) {
        set_error("result cannot be NULL");
        return 1;
    }

    /*
     * Start with an empty result.
     */
    result->str = nullptr;
    result->roots = nullptr;
    result->root_count = 0;
    result->score = 0.0f;

    try {
        equation_generator::Equation equation =
            generator->generator.generate();

        /*
         * Copy the std::string into memory that C can own.
         */
        result->str = copy_string(equation.str);

        if (!result->str) {
            set_error("Failed to allocate equation string");
            return 1;
        }

        /*
         * Copy the vector<float> into a C array.
         */
        result->root_count =
            static_cast<int>(equation.roots.size());

        if (result->root_count > 0) {
            result->roots = static_cast<float *>(
                std::malloc(
                    sizeof(float) * result->root_count
                )
            );

            if (!result->roots) {
                std::free(result->str);
                result->str = nullptr;

                result->root_count = 0;

                set_error("Failed to allocate roots");
                return 1;
            }

            std::memcpy(
                result->roots,
                equation.roots.data(),
                sizeof(float) * result->root_count
            );
        }

        result->score = equation.score;

        return 0;
    }
    catch (const std::exception& e) {
        eg_equation_free(result);
        set_error(e);
        return 1;
    }
    catch (...) {
        eg_equation_free(result);
        set_error("Unknown error generating equation");
        return 1;
    }
}


void eg_equation_free(eg_equation *equation)
{
    if (!equation) {
        return;
    }

    std::free(equation->str);
    std::free(equation->roots);

    equation->str = nullptr;
    equation->roots = nullptr;
    equation->root_count = 0;
    equation->score = 0.0f;
}


const char *eg_last_error(void)
{
    return last_error.c_str();
}

} // extern "C"