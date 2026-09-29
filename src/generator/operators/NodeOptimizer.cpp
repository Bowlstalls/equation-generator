#include "NodeOptimizer.h"

#include <vector>

#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

using namespace equation_generator;

NodeOptimizer::NodeOptimizer(Random& random, const Settings& settings): random(random), settings(settings) {}

std::unique_ptr<Node> NodeOptimizer::optimize(std::unique_ptr<Node> origin) const
{
  return (this->*typeMap.at(origin->type))(std::move(origin));
}

std::unique_ptr<Node> NodeOptimizer::optimizeValueNode(std::unique_ptr<Node> node) const
{
  if (const auto& valueNode = static_cast<ValueNode&>(*node); valueNode.value == 0) {
    return nullptr;
  }
  return node;
}

std::unique_ptr<Node> NodeOptimizer::optimizeAddNode(std::unique_ptr<Node> node) const
{
  const auto start = node->toString();
  auto& multNode = static_cast<MultNode&>(*node);
  std::vector<std::unique_ptr<Node>> newList;
  std::map<float, ValueNode> values;

  for (auto& item : multNode.list) {
    auto optimized = optimize(std::move(item));
    if (!optimized) {
      continue;
    }
    if (optimized->type != NodeType::ValueNode) {
      newList.push_back(std::move(optimized));
      continue;
    }
    if (auto& valueNode = static_cast<ValueNode&>(*optimized); !values.contains(valueNode.power)) {
      values.emplace(valueNode.power, valueNode);
    } else {
      values.at(valueNode.power) += valueNode;
    }
  }
  for (auto [_, valueNode] : values) {
    if (valueNode.value != 0) {
      newList.push_back(std::make_unique<ValueNode>(valueNode));
    }
  }
  if (newList.size() == 0) {
    return nullptr;
  }
  if (newList.size() == 1) {
    return std::move(newList[0]);
  }
  random.shuffle<std::unique_ptr<Node>>(newList);
  auto res = std::make_unique<AddNode>(std::move(newList));
  return res;
}

std::unique_ptr<Node> NodeOptimizer::optimizeMultNode(std::unique_ptr<Node> node) const
{
  const auto start = node->toString();
  auto& multNode = static_cast<MultNode&>(*node);
  std::vector<std::unique_ptr<Node>> newList;
  auto value = ValueNode(settings.variableName, 1, 0);

  for (auto& item : multNode.list) {
    auto optimized = optimize(std::move(item));
    if (!optimized) {
      return nullptr;
    }
    if (optimized->type != NodeType::ValueNode) {
      newList.push_back(std::move(optimized));
      continue;
    }
    const auto& valueNode = static_cast<ValueNode&>(*optimized);
    value *= valueNode;
  }
  if (value.value == 0) {
    return nullptr;
  }
  if (std::abs(value.value) != 1 || value.power != 0) {
    newList.push_back(std::make_unique<ValueNode>(value));
  }
  if (newList.size() == 0) {
    return nullptr;
  }
  if (newList.size() == 1) {
    return std::move(newList[0]);
  }
  random.shuffle<std::unique_ptr<Node>>(newList);
  auto res = std::make_unique<MultNode>(std::move(newList));
  if (value.value == -1 && value.power == 0) {
    res->negate();
  }
  return res;
}
