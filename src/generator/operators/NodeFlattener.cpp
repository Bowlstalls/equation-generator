#include "NodeFlattener.h"

#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/MultNode.h"

namespace equation_generator {
  static std::unique_ptr<Node> multiplyValueNode(std::unique_ptr<Node> valueNode, std::unique_ptr<Node> other);
  static std::unique_ptr<Node> multiplyAddNode(std::unique_ptr<Node> AddNode, std::unique_ptr<Node> other);

  inline static std::map<
      NodeType,
      std::unique_ptr<Node>(*)(std::unique_ptr<Node>, std::unique_ptr<Node>)
    > typeMap = {
    {NodeType::ValueNode, multiplyValueNode},
    {NodeType::AddNode, multiplyAddNode}
    };

  static std::unique_ptr<Node> operator*(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  {
    return typeMap.at(lhs->type)(std::move(lhs), std::move(rhs));
  }

  std::unique_ptr<Node> NodeFlattener::flatten(std::unique_ptr<Node> node)
  {
    return typeMap.at(node->type)(std::move(node));
  }

  std::unique_ptr<Node> NodeFlattener::flattenAddNode(std::unique_ptr<Node> node)
  {
    for (auto& addNode = static_cast<AddNode&>(*node); auto& item : addNode.list) {
      item = flatten(std::move(item));
    }
    return node;
  }

  std::unique_ptr<Node> NodeFlattener::flattenMultNode(std::unique_ptr<Node> node)
  {
    auto& multNode = static_cast<MultNode&>(*node);
    auto& list = multNode.list;
    if (list.size() == 0) {
      return std::make_unique<AddNode>();
    }
    std::unique_ptr<Node> res = flatten(std::move(list[0]));
    for (auto i = 1; i < list.size(); ++i) {
      res = std::move(res) * flatten(std::move(list.at(i)));
    }
    return std::move(res);
  }

  std::unique_ptr<Node> multiplyValueNode(std::unique_ptr<Node> node, std::unique_ptr<Node> other)
  {
    if (other->type != NodeType::ValueNode) {
      return std::move(other) * std::move(node);
    }
    auto& valueNode = static_cast<ValueNode&>(*node);
    const auto& otherValueNode = static_cast<ValueNode&>(*other);
    valueNode *= otherValueNode;
    return node;
  }

  std::unique_ptr<Node> multiplyAddNode(std::unique_ptr<Node> node, std::unique_ptr<Node> other)
  {
    for (auto& addNode = static_cast<AddNode&>(*node); auto& item : addNode.list) {
      item = std::move(item) * other->clone();
    }
    return node;
  }
}
