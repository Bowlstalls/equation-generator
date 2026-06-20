#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "Node.h"

namespace equation_generator {
  class VarNode final : public Node {
  public:
    explicit VarNode(int power);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;

    int power;
  };
}

#endif
