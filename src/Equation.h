#ifndef EQUATION_GENERATOR_EXPRESSION_H
#define EQUATION_GENERATOR_EXPRESSION_H
#include <vector>

#include "nodes/Node.h"

namespace equation_generator {
  struct Equation {
    std::vector<float> roots;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
    float score;

    [[nodiscard]] std::string toString() const {
      return lhs->toString() + " = " + rhs->toString();
    }
  };
}

#endif
