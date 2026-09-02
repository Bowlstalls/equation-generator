#include "NodeNegator.h"

#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

namespace equation_generator {
  std::unique_ptr<Node> NodeNegator::negate(std::unique_ptr<Node> node)
  {
    return typeMap.at(node->type)(std::move(node));
  }

  std::unique_ptr<Node> NodeNegator::negateValueNode(std::unique_ptr<Node> node)
  {
    const auto& valueNode = static_cast<ValueNode&>(*node);
    return std::make_unique<ValueNode>(-valueNode);
  }

  std::unique_ptr<Node> NodeNegator::negateAddNode(std::unique_ptr<Node> node)
  {
    for (auto& addNode = static_cast<AddNode&>(*node); auto& item : addNode.list) {
      item = negate(std::move(item));
    }
    return node;
  }

  std::unique_ptr<Node> NodeNegator::negateMultNode(std::unique_ptr<Node> node)
  {
    auto& multNode = static_cast<MultNode&>(*node);
    multNode.list[0] = negate(std::move(multNode.list[0]));
    return node;
  }
}
