#include "VarNode.h"
#include <utility>
#include "AddNode.h"
#include "MultNode.h"
#include "ValueNode.h"

using namespace equation_generator;

VarNode::VarNode(std::string name, const int value, const int power): ValueNode(NodeType::VarNode, value),
name{std::move(name)},
power{power}
{}

std::unique_ptr<Node> VarNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  if (other->type == NodeType::VarNode) {
    if (power == static_cast<VarNode&>(*other).power) {
      return std::make_unique<MultNode>(std::make_unique<ValueNode>(2), std::move(self));
    }
  }
  return std::make_unique<AddNode>(std::move(self), std::move(other));
}

std::unique_ptr<Node> VarNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  if (other->type == NodeType::VarNode) {
    power += static_cast<VarNode&>(*other).power;
    return self;
  }
  return ValueNode::multiply(std::move(self), std::move(other));
}

std::unique_ptr<Node> VarNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  int otherValue = params.getRandomValue();
  value -= otherValue;
  return std::make_unique<AddNode>(std::move(self), std::make_unique<VarNode>(name, otherValue, power));
}

std::string VarNode::toString() const
{
  std::string res = std::to_string(value) + name;
  if (power != 1) {
    res += '^' + std::to_string(power);
  }
  return res;
}

std::unique_ptr<Node> VarNode::clone() const
{
  return std::make_unique<VarNode>(*this);
}
