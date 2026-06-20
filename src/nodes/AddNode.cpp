#include "AddNode.h"
using namespace equation_generator;

AddNode::AddNode(const std::vector<std::unique_ptr<Node>>& list): list{list} {}

AddNode::AddNode(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
{
  insertNode<AddNode>(NodeType::AddNode, list, std::move(lhs));
  insertNode<AddNode>(NodeType::AddNode, list, std::move(rhs));
}

std::unique_ptr<Node> AddNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  insertNode<AddNode>(NodeType::AddNode, list, std::move(other));
  return self;
}

std::unique_ptr<Node> AddNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  for (auto term : list) {
    term->multiply(std::move(term), std::move(other));
  }
  return self;
}
