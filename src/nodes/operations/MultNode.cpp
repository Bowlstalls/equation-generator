#include "MultNode.h"

#include <algorithm>

#include "AddNode.h"
using namespace equation_generator;

MultNode::MultNode(std::vector<std::unique_ptr<Node>>&& list): OperationNode(NodeType::MultNode, 2)
{
  for (auto& item : list) {
    listInsert<MultNode>(NodeType::MultNode, this->list, std::move(item));
  }
}

MultNode::MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): OperationNode(NodeType::MultNode, 2)
{
  listInsert<MultNode>(NodeType::MultNode, this->list, std::move(lhs));
  listInsert<MultNode>(NodeType::MultNode, this->list, std::move(rhs));
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

void MultNode::negate()
{
  if (list.empty()) {
    return;
  }
  list[0]->negate();
}

void MultNode::setBase(const float base)
{
  for (const auto& item : list) {
    item->setBase(base);
  }
}

std::string MultNode::toString() const
{
  auto iterator = list.begin();
  std::string res = getNext(**iterator);
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
  return std::make_unique<MultNode>(std::move(newList));
}
