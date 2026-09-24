#ifndef EQUATION_GENERATOR_API_SETTINGS_H
#define EQUATION_GENERATOR_API_SETTINGS_H

#include <equation-generator/Settings.h>
#include <equation-generator/c/equation_generator.h>

static equation_generator::Settings convert_settings(const eq_settings& settings);

#endif
