#include "MultNode.h"

#include <algorithm>

#include "AddNode.h"
using namespace equation_generator;

MultNode::MultNode(std::vector<std::unique_ptr<Node>> list): Node(NodeType::MultNode, 2), list{std::move(list)} {}

MultNode::MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): Node(NodeType::MultNode, 2)
{
  insertNode<MultNode>(NodeType::MultNode, list, std::move(lhs));
  insertNode<MultNode>(NodeType::MultNode, list, std::move(rhs));
}

std::unique_ptr<Node> MultNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  return std::make_unique<AddNode>(std::move(self), std::move(other));
}

std::unique_ptr<Node> MultNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<MultNode>(NodeType::MultNode, list, std::move(other));
  return self;
}

std::unique_ptr<Node> MultNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  mutateList(list, params);
  const int end = list.size() - 1;
  if (end == 0) {
    return self;
  }
  if (list[0]->type != NodeType::AddNode && list[end]->type == NodeType::AddNode) {
    std::swap(list[0], list[end]);
  }
  list[0] = std::move(list[0]) * std::move(list[end]);
  list.erase(list.begin() + end);
  std::ranges::shuffle(list, params.generator);
  return self;
}

std::unique_ptr<Node> MultNode::negate(std::unique_ptr<Node> self)
{
  list[0]->negate(std::move(list[0]));
  return self;
}

std::string MultNode::toString()
{
  return concatenate(list, " * ", priority);
}

std::unique_ptr<Node> MultNode::clone()
{
  return std::make_unique<MultNode>(cloneList(list));
}
