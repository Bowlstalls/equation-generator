#ifndef EQUATION_GENERATOR_EQUATION_H
#define EQUATION_GENERATOR_EQUATION_H

#include <string>
#include <vector>
#include <equation-generator/Export.h>

namespace equation_generator {
  struct EQUATION_GENERATOR_API Equation {
    std::string str;
    std::vector<float> roots;
    float score;
  };
}

#endif
