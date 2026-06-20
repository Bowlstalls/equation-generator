
#include "MultNode.h"

#include "AddNode.h"
using namespace equation_generator;

MultNode::MultNode(const std::vector<std::unique_ptr<Node>>& list): list{list} {}

MultNode::MultNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
{
  insertNode<MultNode>(NodeType::MultNode, list, std::move(lhs));
  insertNode<MultNode>(NodeType::MultNode, list, std::move(rhs));
}

std::unique_ptr<Node> MultNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  return std::make_unique<AddNode>(self, other);
}

std::unique_ptr<Node> MultNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<MultNode>(NodeType::MultNode, list, std::move(other));
  return self;
}
