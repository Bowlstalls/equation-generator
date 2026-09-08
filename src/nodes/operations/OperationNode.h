#ifndef EQUATION_GENERATOR_OPERATIONNODE_H
#define EQUATION_GENERATOR_OPERATIONNODE_H

#include "../Node.h"


namespace equation_generator {
  class OperationNode : public Node {
  public:
    int priority;

    explicit OperationNode(const NodeType type, const int priority): Node(type), priority(priority) {}

  protected:
    template<typename T>
    static void listInsert(const NodeType type, std::vector<std::unique_ptr<Node>>& list, std::unique_ptr<Node> item)
    {
      if (item->type != type) {
        list.push_back(std::move(item));
        return;
      }
      for (auto& castItem = static_cast<T&>(*item); auto& subitem : castItem.list) {
        list.push_back(std::move(subitem));
      }
    };
  };
}

#endif
