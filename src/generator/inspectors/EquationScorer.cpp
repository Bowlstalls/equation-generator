#include "EquationScorer.h"

#include "../../nodes/ValueNode.h"
#include "../../nodes/operations/AddNode.h"
#include "../../nodes/operations/MultNode.h"

namespace equation_generator {
  float EquationScorer::score(const EquationData& equation)
  {
    Data data;
    data.setRoots(equation.roots);
    score(*equation.lhs, data);
    return data.getTotal();
  }

  void EquationScorer::score(const Node& node, Data& data, const int depth)
  {
    typeMap.at(node.type)(node, data, depth);
  }

  void EquationScorer::scoreValueNode(const Node& node, Data& data, const int depth)
  {
    const auto& valueNode = static_cast<const ValueNode&>(node);
    data.coefficientSize.add(std::to_string(std::abs(static_cast<int>(valueNode.value))).length());
    data.depth.add(depth);
  }

  void EquationScorer::scoreAddNode(const Node& node, Data& data, const int depth)
  {
    const auto& addNode = static_cast<const AddNode&>(node);
    data.width.add(addNode.list.size());
    for (const auto& item : addNode.list) {
      score(*item, data, depth);
    }
  }

  void EquationScorer::scoreMultNode(const Node& node, Data& data, int depth)
  {
    const auto& multNode = static_cast<const MultNode&>(node);
    for (const auto& item : multNode.list) {
      score(*item, data, depth);
      ++depth;
    }
  }
}
