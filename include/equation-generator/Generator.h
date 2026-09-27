#ifndef EQUATION_GENERATOR_GENERATOR_H
#define EQUATION_GENERATOR_GENERATOR_H

#include <memory>
#include <equation-generator/Settings.h>
#include <equation-generator/Equation.h>
#include <equation-generator/Export.h>

namespace equation_generator {
  class GeneratorImpl;

  class EQUATION_GENERATOR_API Generator {
  public:
    explicit Generator(const Settings& settings);
    ~Generator();

    [[nodiscard]] Equation generate() const;

  private:
    std::unique_ptr<GeneratorImpl> impl;
  };
}

#endif
