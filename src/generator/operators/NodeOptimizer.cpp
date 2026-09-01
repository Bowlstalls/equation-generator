#include "NodeOptimizer.h"

#include <vector>

#include "../Generator.h"
#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

using namespace equation_generator;

NodeOptimizer::NodeOptimizer(Generator& generator): random(generator.random), settings(generator.settings) {}

NodeOptimizer::NodeOptimizer(Random& random, const Settings& settings): random(random), settings(settings) {}
}

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
  auto& multNode = static_cast<MultNode&>(*node);
  std::vector<std::unique_ptr<Node>> newList;
  std::map<int, ValueNode> values;

  for (auto& item : multNode.list) {
    auto optimized = optimize(std::move(item));
    if (!optimized) {
      continue;
    }
    if (optimized->type == NodeType::ValueNode) {
      if (auto& valueNode = static_cast<ValueNode&>(*optimized); !values.contains(valueNode.power)) {
        values.emplace(valueNode.power, valueNode);
      } else {
        values.at(valueNode.power) += valueNode;
      }
    } else if (optimized->type == NodeType::AddNode) {
      auto& otherAddNode = static_cast<AddNode&>(*optimized);
      for (auto& otherItem : otherAddNode.list) {
        newList.push_back(std::move(otherItem));
      }
    } else {
      newList.push_back(std::move(optimized));
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
  return std::make_unique<MultNode>(std::move(newList));
}

std::unique_ptr<Node> NodeOptimizer::optimizeMultNode(std::unique_ptr<Node> node) const
{
  auto& multNode = static_cast<MultNode&>(*node);
  std::vector<std::unique_ptr<Node>> newList;
  auto value = ValueNode(settings.variableName, 1, 0);

  for (auto& item : multNode.list) {
    auto optimized = optimize(std::move(item));
    if (!optimized) {
      return nullptr;
    }
    if (optimized->type == NodeType::ValueNode) {
      const auto& valueNode = static_cast<ValueNode&>(*optimized);
      value *= valueNode;
    } else if (optimized->type == NodeType::MultNode) {
      auto& otherMultNode = static_cast<MultNode&>(*optimized);
      for (auto& otherItem : otherMultNode.list) {
        newList.push_back(std::move(otherItem));
      }
    } else {
      newList.push_back(std::move(optimized));
    }
  }
  if (value.value != 0) {
    newList.push_back(std::make_unique<ValueNode>(value));
  }
  if (newList.size() == 0) {
    return nullptr;
  }
  if (newList.size() == 1) {
    return std::move(newList[0]);
  }
  random.shuffle<std::unique_ptr<Node>>(newList);
  return std::make_unique<MultNode>(std::move(newList));
}
