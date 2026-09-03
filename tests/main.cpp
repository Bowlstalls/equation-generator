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
    .degree = 2,
    .targetScore = 5,
    .values = Settings::ValueSettings{.max = 2, .lowBias = 2, .negativeChance = 0.3},
    .roots = Settings::ValueSettings{.max = 5, .lowBias = 1, .negativeChance = 0.3},
    .powers = Settings::ValueSettings{.max = 2, .lowBias = 1, .negativeChance = 0}
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
