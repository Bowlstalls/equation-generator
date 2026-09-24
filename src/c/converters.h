#ifndef EQUATION_GENERATOR_CONVERTERS_H
#define EQUATION_GENERATOR_CONVERTERS_H

#include <equation-generator/Settings.h>
#include <equation-generator/Equation.h>
#include <equation-generator/c/equation_generator.h>

static equation_generator::Settings convert_settings(const eq_settings& settings);
static void convert_equation(eq_equation* out, const equation_generator::Equation& src);

#endif
