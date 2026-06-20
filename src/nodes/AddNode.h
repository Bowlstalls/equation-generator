#ifndef ADDNODE_H
#define ADDNODE_H

#include <memory>
#include <vector>
#include "Node.h"

namespace equation_generator {
  class AddNode final : public Node {
  public:
    explicit AddNode(const std::vector<std::unique_ptr<Node>>& list);
    AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;

    std::vector<std::unique_ptr<Node>> list;
  };
}

#endif
