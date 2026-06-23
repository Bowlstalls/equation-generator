#ifndef VALUENODE_H
#define VALUENODE_H

#include "Node.h"

namespace equation_generator {
  class ValueNode: public Node {
  public:
    int value;

    explicit ValueNode(int value);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> negate(std::unique_ptr<Node> self) override;
    std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) override;

    std::string toString() override;
    std::unique_ptr<Node> clone() override;

  protected:
    ValueNode(NodeType type, int value);
  };
}

#endif
