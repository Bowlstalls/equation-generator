#ifndef EQUATION_GENERATOR_GENERATOR_H
#define EQUATION_GENERATOR_GENERATOR_H

#include "Expression.h"
#include "random.h"
#include "settings.h"
#include "operators/NodeGenerator.h"

namespace equation_generator {
  class Generator {
  public:
    Settings settings;
    Random random;
    NodeGenerator nodeGenerator;

    explicit Generator(const Settings& settings);

    Expression generate(int targetScore);
  };
}


#endif
