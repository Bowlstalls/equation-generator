#include "ValueNode.h"

#include <utility>
#include "operations/AddNode.h"
#include "operations/MultNode.h"

using namespace equation_generator;

ValueNode::ValueNode(const int value): Node(NodeType::ValueNode), value(value) {}

ValueNode::ValueNode(std::string name, const int value, const int power):
Node(NodeType::ValueNode),
value(value),
power(power),
name(std::move(name))
{}

ValueNode ValueNode::operator+(const ValueNode& other) const
{
  if (power != other.power) {
    throw std::invalid_argument("Cannot add values with different power");
  }
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  return ValueNode(name, value + other.value, power);
}

ValueNode ValueNode::operator-(const ValueNode& other) const
{
  if (power != other.power) {
    throw std::invalid_argument("Cannot add values with different power");
  }
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  return ValueNode(name, value - other.value, power);
}

ValueNode ValueNode::operator*(const ValueNode& other) const
{
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  return ValueNode(name, value * other.value, power + other.power);
}

void ValueNode::operator+=(const ValueNode& other)
{
  if (power != other.power) {
    throw std::invalid_argument("Cannot add values with different power");
  }
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  value += other.value;
}

void ValueNode::operator-=(const ValueNode& other)
{
  if (power != other.power) {
    throw std::invalid_argument("Cannot add values with different power");
  }
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  value -= other.value;
}

void ValueNode::operator*=(const ValueNode& other)
{
  if (name != other.name) {
    throw std::invalid_argument("Cannot add two different variables");
  }
  value *= other.value;
  power += other.power;
}

ValueNode ValueNode::operator-() const
{
  return ValueNode(name, -value, power);
}

std::string ValueNode::toString() const
{
  if (!power) {
    return std::to_string(value);
  }
  std::string res;
  if (value == -1) {
    res += '-';
  } else if (value != 1) {
    res += std::to_string(value);
  }
  res += name;
  if (power != 1) {
    res += '^' + std::to_string(power);
  }
  return res;
}

std::unique_ptr<Node> ValueNode::clone() const
{
  return std::make_unique<ValueNode>(*this);
}
