#ifndef EQUATION_GENERATOR_GENERATOR_H
#define EQUATION_GENERATOR_GENERATOR_H

#include "Equation.h"
#include "../../src/generator/random.h"
#include "settings.h"
#include "../../src/generator/operators/NodeGenerator.h"
#include "../../src/generator/operators/NodeOptimizer.h"

namespace equation_generator {
  class Generator {
  public:
    explicit Generator(const Settings& settings);

    Equation generate();

  private:
    Settings settings;
    Random random;
    NodeGenerator nodeGenerator;
    NodeOptimizer nodeOptimizer;

    Equation getRootEquation(int degree);
    void spill(Equation& equation);
  };
}


#endif
