#ifndef EQUATION_GENERATOR_GENERATOR_H
#define EQUATION_GENERATOR_GENERATOR_H

#include <memory>
#include <equation-generator/Settings.h>
#include <equation-generator/Equation.h>

namespace equation_generator {
  class GeneratorImpl;

  class Generator {
  public:
    explicit Generator(const Settings& settings);
    ~Generator();

    Equation generate();

  private:
    std::unique_ptr<GeneratorImpl> impl;
  };
}

#endif
