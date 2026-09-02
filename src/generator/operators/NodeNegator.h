#ifndef EQUATION_GENERATOR_NODENEGATOR_H
#define EQUATION_GENERATOR_NODENEGATOR_H
#include <map>
#include <memory>

#include "../../nodes/Node.h"

namespace equation_generator {
  class NodeNegator {
  public:
    static std::unique_ptr<Node> negate(std::unique_ptr<Node> node);

  private:
    static std::unique_ptr<Node> negateValueNode(std::unique_ptr<Node> node);
    static std::unique_ptr<Node> negateAddNode(std::unique_ptr<Node> node);
    static std::unique_ptr<Node> negateMultNode(std::unique_ptr<Node> node);

    inline static std::map<NodeType, std::unique_ptr<Node>(*)(std::unique_ptr<Node>)> typeMap = {
      {NodeType::ValueNode, negateValueNode},
      {NodeType::AddNode, negateAddNode},
      {NodeType::MultNode, negateMultNode},
    };
  };
} // equation_generator

#endif
