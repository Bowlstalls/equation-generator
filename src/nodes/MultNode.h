#ifndef MULTNODE_H
#define MULTNODE_H

#include <memory>
#include <vector>
#include "Node.h"

namespace equation_generator {
  class MultNode final : public Node {
  public:
    std::vector<std::unique_ptr<Node>> list;

    explicit MultNode(std::vector<std::unique_ptr<Node>> list);
    MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

    std::unique_ptr<Node> add(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other) override;
    std::unique_ptr<Node> negate(std::unique_ptr<Node> self) override;
    std::unique_ptr<Node> mutate(std::unique_ptr<Node> self, GeneratorParams &params) override;

    std::string toString() override;
    std::unique_ptr<Node> clone() override;
  };
}

#endif
