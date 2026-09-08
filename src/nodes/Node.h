#ifndef EQUATION_GENERATOR_INODE_H
#define EQUATION_GENERATOR_INODE_H
#include <memory>

#include "NodeType.h"

namespace equation_generator {
  class Node {
  public:
    NodeType type;

    explicit Node(const NodeType type): type(type) {}
    virtual ~Node() = default;

    virtual void negate() = 0;
    virtual void setBase(float base) = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual std::unique_ptr<Node> clone() const = 0;
  };
}

#endif
