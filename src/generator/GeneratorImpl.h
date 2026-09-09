#ifndef EQUATION_GENERATOR_GENERATORIMPL_H
#define EQUATION_GENERATOR_GENERATORIMPL_H

#include <equation-generator/Settings.h>

#include "EquationData.h"
#include "Random.h"
#include "operators/NodeGenerator.h"
#include "operators/NodeOptimizer.h"

namespace equation_generator {
  class GeneratorImpl {
  public:
    explicit GeneratorImpl(const Settings& settings);

    Equation generate();

  private:
    Settings settings;
    Random random;
    NodeGenerator nodeGenerator;
    NodeOptimizer nodeOptimizer;

    EquationData getRootEquation(int degree);
    void spill(EquationData& equation);
  };
}

#endif
