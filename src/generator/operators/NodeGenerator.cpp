#include "NodeGenerator.h"

#include <map>

#include "../Generator.h"
#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

using namespace equation_generator;

NodeGenerator::NodeGenerator(Generator& generator): random(generator.random), settings(generator.settings) {}
NodeGenerator::NodeGenerator(Random& random, const Settings& settings): random(random), settings(settings) {}

std::unique_ptr<Node> NodeGenerator::generateOperation() const
{
  return generate(random.getOperation());
}

std::unique_ptr<Node> NodeGenerator::generate(const NodeType& type, const int depth, const int width) const
{
  return (this->*typeMap.at(type))(depth, width);
}

std::unique_ptr<Node> NodeGenerator::generateValueNode(const int depth, const int width) const
{
  return std::make_unique<ValueNode>(settings.variableName, random.getValue(depth, width), random.getPower(depth));
}

std::unique_ptr<Node> NodeGenerator::generateAddNode(const int depth, int width) const
{
  if (width >= settings.structureSettings.maxWidth || random.getBool(settings.structureSettings.valueChance)) {
    return generateValueNode(depth, width);
  }
  ++width;
  return std::make_unique<AddNode>(
    generate(random.getOperation(), depth, width),
    generate(random.getOperation(), depth, width)
    );
}

std::unique_ptr<Node> NodeGenerator::generateMultNode(int depth, const int width) const
{
  if (depth >= settings.structureSettings.maxWidth || random.getBool(settings.structureSettings.valueChance)) {
    return generateValueNode(depth, width);
  }
  ++depth;
  return std::make_unique<MultNode>(
    generate(random.getOperation(), depth, width),
    generate(random.getOperation(), depth, width)
    );
}
