#ifndef EQUATION_GENERATOR_ADDNODE_H
#define EQUATION_GENERATOR_ADDNODE_H

#include <memory>
#include <vector>

#include "OperationNode.h"

namespace equation_generator {
  class AddNode final : public OperationNode {
  public:
    std::vector<std::unique_ptr<Node>> list;

    AddNode(): OperationNode(NodeType::AddNode, 1){}
    explicit AddNode(std::vector<std::unique_ptr<Node>>&& list);

    AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

    void negate() override;
    void setBase(float base) override;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::unique_ptr<Node> clone() const override;
  };
}

#endif
