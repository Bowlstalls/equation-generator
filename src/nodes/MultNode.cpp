
#include "MultNode.h"

#include <bits/stl_tree.h>

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

std::string MultNode::toString()
{
  return concatenate(list, " * ", priority);
}

std::unique_ptr<Node> MultNode::clone()
{
  return std::make_unique<MultNode>(cloneList(list));
}

std::unique_ptr<Node> MultNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  mutateList(list, params);
  int i1 = params.getRandomInt(0, list.size() - 1);
  int i2 = params.getRandomInt(0, list.size() - 1);
  while (i1 == i2) {
    i2 = params.getRandomInt(0, list.size() - 1);
  }
  if (list[i1]->type != NodeType::AddNode && list[i1]->type == NodeType::AddNode) {
    std::swap(i1, i2);
  }
  list[i1] = std::move(list[i1]) * std::move(list[i2]);
  list.erase(list.begin() + i2);
  return self;
}

