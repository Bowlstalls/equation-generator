#ifndef VALUENODE_H
#define VALUENODE_H

#include "Node.h"

namespace equation_generator {
  class ValueNode final : public Node {
  public:
    explicit ValueNode(int value);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) override;
    std::string toString() override;
    std::unique_ptr<Node> clone() override;

    int value;
  };
}

#endif
