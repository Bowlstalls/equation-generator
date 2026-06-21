#include "AddNode.h"
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
  int i1 = params.getRandomInt(0, list.size() - 1);
  int i2 = params.getRandomInt(0, list.size() - 1);
  while (i1 == i2) {
    i2 = params.getRandomInt(0, list.size() - 1);
  }
  list[i1] = std::move(list[i1]) + std::move(list[i2]);
  list.erase(list.begin() + i2);
  return self;
}
