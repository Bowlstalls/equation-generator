#ifndef EQUATION_GENERATOR_INTERNALSETTINGS_H
#define EQUATION_GENERATOR_INTERNALSETTINGS_H
#include <equation-generator/Settings.h>

#include "../nodes/NodeType.h"

namespace equation_generator {
  struct ImplSettings : Settings {
    std::map<NodeType, int> operationWeights;

    explicit ImplSettings(const Settings& settings): Settings(settings)
    {
      operationWeights = {
        {NodeType::AddNode, settings.structureSettings.operation_weights.add},
        {NodeType::MultNode, settings.structureSettings.operation_weights.mult}
      };
    }
  };
}

#endif
