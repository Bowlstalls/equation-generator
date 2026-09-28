#include <equation-generator/c/equation_generator.h>
#include <equation-generator/Generator.h>
#include <equation-generator/Settings.h>

#include "converters.h"

struct eq_generator {
  equation_generator::Generator generator;

  explicit eq_generator(const equation_generator::Settings& settings): generator(settings) {}
};

extern "C" {
eq_generator* eq_generator_create(const eq_settings* settings)
{
  return new eq_generator(convert_settings(*settings));
}

void eq_generator_destroy(eq_generator* generator)
{
  delete generator;
}

void eq_generator_generate(const eq_generator* generator, eq_equation* equation)
{
  const equation_generator::Equation res = generator->generator.generate();
  convert_equation(equation, res);
}

void eq_equation_destroy(eq_equation* equation)
{
  delete[] equation->roots;
  delete[] equation->str;
}
}

void eq_set_defaults(eq_settings* settings)
{
  settings->seed = std::random_device{}();
  settings->variable_name = "x";
  settings->degree = 2;

  settings->value_settings.base = 1;

  settings->value_settings.values.max = 20;
  settings->value_settings.values.low_bias = 2;
  settings->value_settings.values.negative_chance = 0.3;

  settings->value_settings.roots.max = 10;
  settings->value_settings.roots.low_bias = 1;
  settings->value_settings.roots.negative_chance = 0.3;

  settings->value_settings.powers.max = 2;
  settings->value_settings.powers.low_bias = 1;
  settings->value_settings.powers.negative_chance = 0;

  settings->structure_settings.max_depth = 3;
  settings->structure_settings.max_width = 4;
  settings->structure_settings.value_chance = 0.3;
  settings->structure_settings.right_side_chance = 0.2;

  settings->structure_settings.operation_weights.add = 2;
  settings->structure_settings.operation_weights.mult = 1;
}
