#ifndef EQUATION_GENERATOR_EQUATION_H
#define EQUATION_GENERATOR_EQUATION_H
#include <string>
#include <vector>

namespace equation_generator {
  struct Equation {
    std::string str;
    std::vector<float> roots;
    float score;
  };
}

#endif
