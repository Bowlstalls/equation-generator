#ifndef EQUATION_GENERATOR_NODES_H
#define EQUATION_GENERATOR_NODES_H

#include <memory>

#include "../../nodes/NodeType.h"
#include "../random.h"
#include "../settings.h"
#include "../../nodes/Node.h"

namespace equation_generator {
  class Generator;

  class NodeGenerator {
  public:
    Random& random;
    const Settings& settings;

    explicit NodeGenerator(Generator& generator);
    NodeGenerator(Random& random, const Settings& settings);

    [[nodiscard]] std::unique_ptr<Node> generateOperation() const;
    [[nodiscard]] std::unique_ptr<Node> generate(const NodeType& type, int depth = 1, int width = 1) const;

  private:
    [[nodiscard]] std::unique_ptr<Node> generateValueNode(int depth, int width) const;
    [[nodiscard]] std::unique_ptr<Node> generateAddNode(int depth, int width) const;
    [[nodiscard]] std::unique_ptr<Node> generateMultNode(int depth, int width) const;

    inline static const std::map<NodeType, std::unique_ptr<Node>(NodeGenerator::*)(int, int) const> typeMap = {
      {NodeType::ValueNode, &NodeGenerator::generateValueNode},
      {NodeType::AddNode, &NodeGenerator::generateAddNode},
      {NodeType::MultNode, &NodeGenerator::generateMultNode}
    };
  };
}

#endif
