#include "../NodeGenerator.h"

#include <iostream>
#include <map>

#include "../Generator.h"
#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

using namespace equation_generator;

NodeGenerator::NodeGenerator(Generator& generator): random(generator.random), settings(generator.settings) {}
NodeGenerator::NodeGenerator(Random& random, const Settings& settings): random(random), settings(settings) {}

std::unique_ptr<Node> NodeGenerator::generateOperation(const int targetScore) const
{
  return generate(random.getOperation(), targetScore);
}

std::unique_ptr<Node> NodeGenerator::generate(const NodeType& type, const int targetScore) const
{
  if (targetScore <= 0) {
    return generateValueNode(0);
  }
  const std::map<NodeType, std::unique_ptr<Node>(NodeGenerator::*)(int) const> typeMap = {
    {NodeType::ValueNode, &NodeGenerator::generateValueNode},
    {NodeType::AddNode, &NodeGenerator::generateAddNode},
    {NodeType::MultNode, &NodeGenerator::generateMultNode}
  };
  return (this->*typeMap.at(type))(targetScore);
}

std::unique_ptr<Node> NodeGenerator::generateValueNode(int) const
{
  return std::make_unique<ValueNode>(settings.variableName, random.getValue(), random.getPower());
}

std::unique_ptr<Node> NodeGenerator::generateAddNode(const int targetScore) const
{
  float lhs = random.getFloat();
  float rhs = random.getFloat();
  const float sum = lhs + rhs;
  lhs *= static_cast<float>(targetScore) / sum;
  rhs *= static_cast<float>(targetScore) / sum;
  return std::make_unique<AddNode>(
    generateOperation(static_cast<int>(lhs)),
    generateOperation(static_cast<int>(rhs))
    );
}

std::unique_ptr<Node> NodeGenerator::generateMultNode(const int targetScore) const
{
  float lhs = random.getFloat();
  float rhs = random.getFloat();
  const float product = lhs * rhs;
  lhs *= std::sqrt(static_cast<float>(targetScore) / product);
  rhs *= std::sqrt(static_cast<float>(targetScore) / product);
  return std::make_unique<MultNode>(
      generateOperation(static_cast<int>(lhs)),
      generateOperation(static_cast<int>(rhs))
    );
}
