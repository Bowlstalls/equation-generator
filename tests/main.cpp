#include <iostream>

#include "../src/generator/Generator.h"
#include "../src/generator/settings.h"
using namespace equation_generator;

int main()
{
  const Settings settings {
    .variableName = "x",
    .values = Settings::ValueSettings{.max = 40, .lowBias = 2, .negativeChance = 0.3},
    .roots = Settings::ValueSettings{.max = 5, .lowBias = 2, .negativeChance = 0.3},
    .powers = Settings::ValueSettings{.max = 2, .lowBias = 1, .negativeChance = 0}
  };
  const Generator generator(settings);
  std::cout << generator.nodeGenerator.generateOperation(5)->toString();
};
