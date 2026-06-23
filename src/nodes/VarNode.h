#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "Node.h"
#include "ValueNode.h"

namespace equation_generator {
  class VarNode final : public ValueNode {
  public:
    std::string name;
    int power;

    VarNode(std::string name, int value, int power);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) override;

    std::string toString() override;
    std::unique_ptr<Node> clone() override;
  };
}

#endif
