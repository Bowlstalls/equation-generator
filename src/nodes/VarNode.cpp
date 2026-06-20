#include "VarNode.h"

#include "AddNode.h"
#include "MultNode.h"
#include "ValueNode.h"

using namespace equation_generator;

VarNode::VarNode(const int power): power{power} {}

std::unique_ptr<Node> VarNode::add(std::unique_ptr<Node> self, const std::unique_ptr<Node> other)
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
  return std::make_unique<MultNode>(std::move(self), std::move(other));
}
