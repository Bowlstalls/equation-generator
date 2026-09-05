#include <iostream>

#include "../src/generator/Generator.h"
#include "../src/generator/settings.h"
#include "tools/EquationVerifier.h"
using namespace equation_generator;

int main()
{
  const Settings settings {
    .seed = std::random_device{}(),
    .variableName = "x",
    .valueSettings = ValueSettings {
      .values = ValueSettings::Item{.max = 20, .lowBias = 2, .negativeChance = 0.3},
      .roots = ValueSettings::Item{.max = 5, .lowBias = 1, .negativeChance = 0.3},
      .powers = ValueSettings::Item{.max = 2, .lowBias = 1, .negativeChance = 0}
    },
    .structureSettings = StructureSettings {
      .maxDepth = 8,
      .maxWidth = 10,
      .degree = 2,
      .valueChance = 0.3
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
