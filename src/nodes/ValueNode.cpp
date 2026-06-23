#include "ValueNode.h"
#include "AddNode.h"
#include "MultNode.h"

using namespace equation_generator;

ValueNode::ValueNode(const int value): Node(NodeType::ValueNode, 10), value{value} {}
ValueNode::ValueNode(const NodeType type, const int value): Node(type, 10), value{value} {}

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

std::unique_ptr<Node> ValueNode::negate(std::unique_ptr<Node> self)
{
  value -= 1;
  return self;
}

std::unique_ptr<Node> ValueNode::mutate(std::unique_ptr<Node> self, GeneratorParams &params)
{
  int otherValue = params.getRandomValue();
  value -= otherValue;
  return std::make_unique<AddNode>(std::move(self), std::make_unique<ValueNode>(otherValue));
}

std::string ValueNode::toString() const
{
  return std::to_string(value);
}

std::unique_ptr<Node> ValueNode::clone() const
{
  return std::make_unique<ValueNode>(*this);
}
