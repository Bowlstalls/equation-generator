#include "equation_generator.h"

#include <equation-generator/Generator.h>
#include <equation-generator/Settings.h>

struct eq_generator {
  equation_generator::Generator generator;

  eq_generator(): generator(equation_generator::Settings{}) {}
};

extern "C" {
eq_generator* eq_generator_create()
{
  return new eq_generator();
}

void eq_generator_destroy(eq_generator* generator)
{
  delete generator;
}
}
