#ifndef EQUATION_GENERATOR_EQUATIONDATA_H
#define EQUATION_GENERATOR_EQUATIONDATA_H
#include <vector>

#include <equation-generator/Equation.h>
#include "../nodes/Node.h"

namespace equation_generator {
  struct EquationData {
    std::vector<float> roots;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
    float score;

    [[nodiscard]] std::string toString() const {
      return lhs->toString() + " = " + rhs->toString();
    }
    [[nodiscard]] Equation toEquation() const
    {
      return Equation{
        .str = toString(),
        .roots = roots,
        .score = score
      };
    }
  };
}

#endif
