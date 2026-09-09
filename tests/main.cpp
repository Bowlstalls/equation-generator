#include <iostream>

#include "../include/equation-generator/Generator.h"
#include "../include/equation-generator/Settings.h"
#include "tools/EquationVerifier.h"
using namespace equation_generator;

int main()
{
  const Settings settings {
    .degree = 2,
  };

  Generator generator(settings);
  const Equation res = generator.generate();
  std::cout << res.toString() << "\n";
  std::cout << "roots: " << "\n";
  for (const auto root : res.roots) {
    std::cout << root << " ";
  }
  std::cout << "\nscore: " << res.score;
};
