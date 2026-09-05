#ifndef EQUATION_GENERATOR_SETTINGS_H
#define EQUATION_GENERATOR_SETTINGS_H
#include <map>

namespace equation_generator {
  struct ValueSettings {
    struct Item {
      int max;
      float lowBias;
      float negativeChance;
    };
    Item values;
    Item roots;
    Item powers;
  };
  struct StructureSettings {
    int maxDepth;
    int maxWidth;
    int degree;
    float rightSideChance = 0.2;
    std::map<NodeType, int> operationWeights = {
      {NodeType::AddNode, 2},
      {NodeType::MultNode, 1}
    };
  };

  struct Settings {
    const unsigned seed;
    std::string variableName = "x";

    ValueSettings valueSettings;
    StructureSettings structureSettings;
  };
}

#endif
