#include <assert.h>
#include <iostream>
#include <equation-generator/Settings.h>
#include "../src/generator/GeneratorImpl.h"
#include "tools/EquationVerifier.h"

using namespace equation_generator;

int main()
{
  for (auto i = 1; i < 10000; ++i) {
    const Settings settings {
      .degree = i % 5
    };
    GeneratorImpl generator(settings);
    const EquationData res = generator.generate();
    assert(EquationVerifier::verify(res));
  }
};
