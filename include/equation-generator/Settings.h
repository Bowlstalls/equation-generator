#ifndef EQUATION_GENERATOR_SETTINGS_H
#define EQUATION_GENERATOR_SETTINGS_H
#include <map>
#include <random>

namespace equation_generator {
  enum class Operation {
    Add,
    Mult
  };
  struct ValueSettings {
    struct Item {
      int max;
      float lowBias;
      float negativeChance;
    };
    float base = 1;
    Item values = Item{.max = 20, .lowBias = 2, .negativeChance = 0.3};
    Item roots = Item{.max = 10, .lowBias = 1, .negativeChance = 0.3};
    Item powers = Item{.max = 2, .lowBias = 1, .negativeChance = 0};
  };
  struct StructureSettings {
    int maxDepth = 3;
    int maxWidth = 4;
    float valueChance = 0.3;
    float rightSideChance = 0.2;
    std::map<Operation, int> operationWeights = {
      {Operation::Add, 2},
      {Operation::Mult, 1}
    };
  };
  struct Settings {
    const unsigned seed = std::random_device{}();
    std::string variableName = "x";
    int degree = 2;

    ValueSettings valueSettings = ValueSettings{};
    StructureSettings structureSettings = StructureSettings{};
  };
}

#endif
