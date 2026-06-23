#include "AddNode.h"

#include <algorithm>
using namespace equation_generator;

AddNode::AddNode(std::vector<std::unique_ptr<Node>> list): Node(NodeType::AddNode, 1), list{std::move(list)} {}

AddNode::AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): Node(NodeType::AddNode, 1)
{
  insertNode<AddNode>(NodeType::AddNode, list, std::move(lhs));
  insertNode<AddNode>(NodeType::AddNode, list, std::move(rhs));
}

std::unique_ptr<Node> AddNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<AddNode>(NodeType::AddNode, list, std::move(other));
  return self;
}

std::unique_ptr<Node> AddNode::multiply(std::unique_ptr<Node> self, const std::unique_ptr<Node> other)
{
  for (auto& term : list) {
    term = term->multiply(std::move(term), other->clone());
  }
  return self;
}

std::string AddNode::toString()
{
  return concatenate(list, " + ", priority);
}

std::unique_ptr<Node> AddNode::clone()
{
  return std::make_unique<AddNode>(cloneList(list));
}

std::unique_ptr<Node> AddNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  mutateList(list, params);
  const int end = list.size() - 1;
  if (end == 0) {
    return self;
  }
  list[0] = std::move(list[0]) + std::move(list[end]);
  list.erase(list.begin() + end);
  std::ranges::shuffle(list, params.generator);
  return self;
}

std::unique_ptr<Node> AddNode::negate(std::unique_ptr<Node> self)
{
  for (auto& term : list) {
    term = term->negate(std::move(term));
  }
  return self;
}
