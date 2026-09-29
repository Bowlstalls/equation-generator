#include <equation-generator/Generator.h>

#include "GeneratorImpl.h"

namespace equation_generator {
  Generator::Generator(const Settings& settings): impl(std::make_unique<GeneratorImpl>(settings)) {}

  Generator::~Generator() = default;

  Equation Generator::generate() const
  {
    return impl->generate().toEquation();
  }
}
