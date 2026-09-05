#include <iostream>

#include "../src/generator/Generator.h"
#include "../src/generator/settings.h"
#include "tools/EquationVerifier.h"
using namespace equation_generator;

int main()
{
  const Settings settings {
    .degree = 2,
    .structureSettings = StructureSettings {
      .maxDepth = 8,
      .maxWidth = 10
    }
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
