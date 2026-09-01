#include "AddNode.h"

#include <algorithm>

#include "../ValueNode.h"
using namespace equation_generator;

AddNode::AddNode(std::vector<std::unique_ptr<Node>>&& list):
OperationNode(NodeType::AddNode, 1),
list(std::move(list))
{}

AddNode::AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): OperationNode(NodeType::AddNode, 1)
{
  list.push_back(std::move(lhs));
  list.push_back(std::move(rhs));
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
