#ifndef EQUATION_GENERATOR_SETTINGS_H
#define EQUATION_GENERATOR_SETTINGS_H
#include <map>

namespace equation_generator {
  struct Settings {
    struct ValueSettings {
      int max;
      float lowBias;
      float negativeChance;
    };

    std::string variableName = "x";
    ValueSettings values;
    ValueSettings roots;
    ValueSettings powers;
    std::map<NodeType, int> typeWeights = {
      {NodeType::AddNode, 2},
      {NodeType::MultNode, 2}
    };
  };
}

#endif
