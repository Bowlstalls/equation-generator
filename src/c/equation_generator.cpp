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
}
