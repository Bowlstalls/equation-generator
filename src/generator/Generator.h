#ifndef EQUATION_GENERATOR_GENERATOR_H
#define EQUATION_GENERATOR_GENERATOR_H

#include "../Equation.h"
#include "random.h"
#include "settings.h"
#include "../nodes/operations/AddNode.h"
#include "operators/NodeGenerator.h"
#include "operators/NodeOptimizer.h"

namespace equation_generator {
  class Generator {
  public:
    Settings settings;
    Random random;
    NodeGenerator nodeGenerator;
    NodeOptimizer nodeOptimizer;

    explicit Generator(const Settings& settings);

    Equation generate();

  private:
    Equation getRootEquation(int degree);
    void spill(Equation& equation);
  };
}


#endif
