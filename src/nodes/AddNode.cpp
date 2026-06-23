#include "AddNode.h"

#include <algorithm>
using namespace equation_generator;

AddNode::AddNode(std::vector<std::unique_ptr<Node>>&& list): Node(NodeType::AddNode, 1), list{std::move(list)} {}

AddNode::AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): Node(NodeType::AddNode, 1)
{
  insertNode<AddNode>(*this, std::move(lhs));
  insertNode<AddNode>(*this, std::move(rhs));
}

std::unique_ptr<Node> AddNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<AddNode>(*this, std::move(other));
  return self;
}

std::unique_ptr<Node> AddNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  auto lambda = [&other](std::unique_ptr<Node> node) -> std::unique_ptr<Node> {
    return std::move(node) * other->clone();
  };
  map<AddNode>(*this, lambda);
  return self;
}

std::unique_ptr<Node> AddNode::negate(std::unique_ptr<Node> self)
{
  auto lambda = [](std::unique_ptr<Node> node) -> std::unique_ptr<Node> {
    return -std::move(node);
  };
  map<AddNode>(*this, lambda);
  return self;
}

std::unique_ptr<Node> AddNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  if (!params.doMutate()) {
    return self;
  }
  mutateList<AddNode>(*this, params);
  if (list.size() == 1) {
    return std::move(list[0]);
  }
  insertNode<AddNode>(*this, std::move(list[0]) + std::move(list[1]));
  list.erase(list.begin(), list.begin() + 2);
  if (list.size() == 1) {
    return std::move(list[0]);
  }
  std::ranges::shuffle(list, params.generator);
  return self;
}

std::string AddNode::toString() const
{
  return concatenate(list, " + ", priority);
}

std::unique_ptr<Node> AddNode::clone() const
{
  return std::make_unique<AddNode>(cloneList(list));
}