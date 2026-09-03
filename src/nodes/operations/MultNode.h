#ifndef EQUATION_GENERATOR_MULTNODE_H
#define EQUATION_GENERATOR_MULTNODE_H

#include <memory>
#include <vector>

#include "OperationNode.h"

namespace equation_generator {
  class MultNode final : public OperationNode {
  public:
    std::vector<std::unique_ptr<Node>> list;

    MultNode(): OperationNode(NodeType::MultNode, 2){}
    explicit MultNode(std::vector<std::unique_ptr<Node>>&& list);

    MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

    void negate() override;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::unique_ptr<Node> clone() const override;
  };
}

#endif
