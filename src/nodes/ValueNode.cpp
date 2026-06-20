#include "ValueNode.h"

#include "AddNode.h"
#include "MultNode.h"

using namespace equation_generator;

ValueNode::ValueNode(const float value): value{value} {}

std::unique_ptr<Node> ValueNode::add(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  if (other->type == NodeType::ValueNode) {
    value += static_cast<ValueNode&>(*other).value;
    return self;
  }
  return std::make_unique<AddNode>(std::move(self), std::move(other));
}

std::unique_ptr<Node> ValueNode::multiply(std::unique_ptr<Node> self, std::unique_ptr<Node> other)
{
  if (other->type == NodeType::ValueNode) {
    value *= static_cast<ValueNode&>(*other).value;
    return self;
  }
  return std::make_unique<MultNode>(std::move(self), std::move(other));
}
