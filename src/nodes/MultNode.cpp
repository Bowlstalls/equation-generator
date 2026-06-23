#include "MultNode.h"

#include <algorithm>

#include "AddNode.h"
using namespace equation_generator;

MultNode::MultNode(std::vector<std::unique_ptr<Node>>&& list): Node(NodeType::MultNode, 2), list{std::move(list)} {}

MultNode::MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs): Node(NodeType::MultNode, 2)
{
  insertNode<MultNode>(*this, std::move(lhs));
  insertNode<MultNode>(*this, std::move(rhs));
}

std::unique_ptr<Node> MultNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  return std::make_unique<AddNode>(std::move(self), std::move(other));
}

std::unique_ptr<Node> MultNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<MultNode>(*this, std::move(other));
  return self;
}

std::unique_ptr<Node> MultNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  if (!params.doMutate()) {
    return self;
  }
  mutateList<MultNode>(*this, params);
  if (list.size() == 1) {
    return std::move(list[0]);
  }
  if (list[0]->type != NodeType::AddNode && list[1]->type == NodeType::AddNode) {
    std::swap(list[0], list[1]);
  }
  insertNode<MultNode>(*this, std::move(list[0]) * std::move(list[1]));
  list.erase(list.begin(), list.begin() + 2);
  if (list.size() == 1) {
    return std::move(list[0]);
  }
  std::ranges::shuffle(list, params.generator);
  return self;
}

std::unique_ptr<Node> MultNode::negate(std::unique_ptr<Node> self)
{
  insertNode<MultNode>(*this, -std::move(list[0]));
  list.erase(list.begin());
  return self;
}

std::string MultNode::toString() const
{
  return concatenate(list, " * ", priority);
}

std::unique_ptr<Node> MultNode::clone() const
{
  return std::make_unique<MultNode>(cloneList(list));
}
