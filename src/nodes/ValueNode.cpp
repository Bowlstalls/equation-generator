#include "ValueNode.h"

#include <cmath>
#include <sstream>
#include <utility>
#include "operations/AddNode.h"
#include "operations/MultNode.h"

using namespace equation_generator;

ValueNode::ValueNode(const float value): Node(NodeType::ValueNode), value(value) {}

ValueNode::ValueNode(std::string name, const float value, const int power):
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

void ValueNode::negate()
{
  value = -value;
}

void ValueNode::setBase(const float base)
{
  value = std::ceil(value) * base;
}

std::string ValueNode::toString() const
{
  std::ostringstream res;
  if (!power) {
    res << value;
    return res.str();
  }
  if (value == -1) {
    res << '-';
  } else if (value != 1) {
    res << value;
  }
  res << name;
  if (power != 1) {
    res << '^' << power;
  }
  return res.str();
}

std::unique_ptr<Node> ValueNode::clone() const
{
  return std::make_unique<ValueNode>(*this);
}
