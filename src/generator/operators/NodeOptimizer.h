#ifndef EQUATION_GENERATOR_NODEOPTIMIZER_H
#define EQUATION_GENERATOR_NODEOPTIMIZER_H
#include <map>
#include <memory>

#include "../random.h"
#include "../settings.h"
#include "../../nodes/NodeType.h"
#include "../../nodes/Node.h"

namespace equation_generator {
  class Generator;

  class NodeOptimizer {
  public:
    Random& random;
    const Settings& settings;

    explicit NodeOptimizer(Generator& generator);
    NodeOptimizer(Random& random, const Settings& settings);

    std::unique_ptr<Node> optimize(std::unique_ptr<Node> origin) const;

  private:
    std::unique_ptr<Node> optimizeValueNode(std::unique_ptr<Node> node) const;
    std::unique_ptr<Node> optimizeAddNode(std::unique_ptr<Node> node) const;
    std::unique_ptr<Node> optimizeMultNode(std::unique_ptr<Node> node) const;

    inline static const std::map<NodeType, std::unique_ptr<Node>(NodeOptimizer::*)(std::unique_ptr<Node>) const> typeMap = {
      {NodeType::ValueNode, &NodeOptimizer::optimizeValueNode},
      {NodeType::AddNode, &NodeOptimizer::optimizeAddNode},
      {NodeType::MultNode, &NodeOptimizer::optimizeMultNode},
    };
  };
}

#endif
