#include "MultNode.h"

#include <algorithm>

#include "AddNode.h"
using namespace equation_generator;

MultNode::MultNode(std::vector<std::unique_ptr<Node>>&& list):
OperationNode(NodeType::MultNode, 2),
list(std::move(list))
{}

MultNode::MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): OperationNode(NodeType::MultNode, 2)
{
  list.push_back(std::move(lhs));
  list.push_back(std::move(rhs));
}

static std::string getNext(const Node& node)
{
  std::string res = node.toString();
  const auto opNode = dynamic_cast<const OperationNode*>(&node);
  if ((opNode && opNode->priority < 2) || res[0] == '-') {
    res = "(" + res + ")";
  }
  return res;
}

std::string MultNode::toString() const
{
  auto iterator = list.begin();
  std::string res = (*iterator)->toString();
  ++iterator;
  for (; iterator < list.end(); ++iterator) {
    res += " * " + getNext(**iterator);
  }
  return res;
}

std::unique_ptr<Node> MultNode::clone() const
{
  std::vector<std::unique_ptr<Node>> newList;
  for (auto& i : list) {
    newList.push_back(i->clone());
  }
  return std::make_unique<AddNode>(std::move(newList));
}
