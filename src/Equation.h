#ifndef EQUATION_GENERATOR_EXPRESSION_H
#define EQUATION_GENERATOR_EXPRESSION_H
#include <vector>

#include "nodes/Node.h"

namespace equation_generator {
  struct Equation {
    std::vector<int> roots;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;

    [[nodiscard]] std::string toString() const;
  };
}

#endif
