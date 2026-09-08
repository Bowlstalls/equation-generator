#ifndef EQUATION_GENERATOR_NODEFLATTENER_H
#define EQUATION_GENERATOR_NODEFLATTENER_H
#include <map>
#include <memory>
#include "../../nodes/operations/AddNode.h"

namespace equation_generator {
  class NodeFlattener {
  public:
    static std::unique_ptr<Node> flatten(std::unique_ptr<Node> node);

  private:
    static std::unique_ptr<Node> flattenAddNode(std::unique_ptr<Node> addNode);
    static std::unique_ptr<Node> flattenMultNode(std::unique_ptr<Node> multNode);

    inline static std::map<NodeType, std::unique_ptr<Node>(*)(std::unique_ptr<Node>)> typeMap = {
      {NodeType::ValueNode, [](std::unique_ptr<Node>node){return node;}},
      {NodeType::AddNode, flattenAddNode},
      {NodeType::MultNode, flattenMultNode}
    };
  };
}

#endif
