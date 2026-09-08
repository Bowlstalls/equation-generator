#include "AddNode.h"

#include <algorithm>

#include "../ValueNode.h"
using namespace equation_generator;

AddNode::AddNode(std::vector<std::unique_ptr<Node>>&& list): OperationNode(NodeType::AddNode, 1)
{
  setList(std::move(list));
}

AddNode::AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): OperationNode(NodeType::AddNode, 1)
{
  listInsert<AddNode>(NodeType::AddNode, list, std::move(lhs));
  listInsert<AddNode>(NodeType::AddNode, list, std::move(rhs));
}

void AddNode::setList(std::vector<std::unique_ptr<Node>>&& newList)
{
  list.clear();
  for (auto& item : newList) {
    listInsert<AddNode>(NodeType::AddNode, list, std::move(item));
  }
}

void AddNode::negate()
{
  for (const auto& node : list) {
    node->negate();
  }
}

void AddNode::setBase(const float base)
{
  for (const auto& item : list) {
    item->setBase(base);
  }
}

std::string AddNode::toString() const
{
  auto iterator = list.begin();
  std::string res = (*iterator)->toString();
  ++iterator;
  for (; iterator < list.end(); ++iterator) {
    auto next = (*iterator)->toString();
    if (next[0] != '-') {
      res += " + " + next;
      continue;
    }
    res += " - ";
    res.append(++next.begin(), next.end());
  }
  return res;
}

std::unique_ptr<Node> AddNode::clone() const
{
  std::vector<std::unique_ptr<Node>> newList;
  for (auto& i : list) {
    newList.push_back(i->clone());
  }
  return std::make_unique<AddNode>(std::move(newList));
}
