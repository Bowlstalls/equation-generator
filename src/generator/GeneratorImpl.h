#ifndef EQUATION_GENERATOR_GENERATORIMPL_H
#define EQUATION_GENERATOR_GENERATORIMPL_H

#include "ImplSettings.h"
#include "EquationData.h"
#include "Random.h"
#include "operators/NodeGenerator.h"
#include "operators/NodeOptimizer.h"

namespace equation_generator {
  class GeneratorImpl {
  public:
    explicit GeneratorImpl(const Settings& settings);

    EquationData generate();

  private:
    ImplSettings settings;
    Random random;
    NodeGenerator nodeGenerator;
    NodeOptimizer nodeOptimizer;

    EquationData getRootEquation(int degree);
    void spill(EquationData& equation);
  };
}

#endif
