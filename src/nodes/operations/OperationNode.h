#ifndef EQUATION_GENERATOR_OPERATIONNODE_H
#define EQUATION_GENERATOR_OPERATIONNODE_H

#include "../Node.h"


namespace equation_generator {
  class OperationNode : public Node {
  public:
    int priority;

    explicit OperationNode(const NodeType type, const int priority): Node(type), priority(priority) {}
  };
}

#endif
