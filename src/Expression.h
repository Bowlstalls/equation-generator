#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>

#include "nodes/Node.h"

namespace equation_generator {
  class Expression {
  public:
    std::vector<int> roots;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;

    explicit Expression(const std::vector<int>& roots);

    void mutate(GeneratorParams& params);
    std::string toString() const;
  };
}

#endif
