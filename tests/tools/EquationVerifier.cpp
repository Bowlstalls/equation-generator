#include "EquationVerifier.h"

#include <cmath>

#include "../../src/nodes/ValueNode.h"
#include "../../src/nodes/operations/AddNode.h"
#include "../../src/nodes/operations/MultNode.h"

namespace equation_generator {
  bool EquationVerifier::verify(const EquationData& equation)
  {
    for (auto& root : equation.roots) {
      if (calculate(*equation.lhs, root) != calculate(*equation.rhs, root)) {
        return false;
      }
    }
    return true;
  }

  int EquationVerifier::calculate(const Node& node, const int root)
  {
    return typeMap.at(node.type)(node, root);
  }

  int EquationVerifier::calculateValueNode(const Node& node, const int root)
  {
    const auto& valueNode = static_cast<const ValueNode&>(node);
    return valueNode.value * std::pow(root, valueNode.power);
  }

  int EquationVerifier::calculateAddNode(const Node& node, const int root)
  {
    const auto& addNode = static_cast<const AddNode&>(node);
    int res = 0;
    for (const auto& item : addNode.list) {
      res += calculate(*item, root);
    }
    return res;
  }

  int EquationVerifier::calculateMultNode(const Node& node, const int root)
  {
    const auto& multNode = static_cast<const MultNode&>(node);
    int res = 1;
    for (const auto& item : multNode.list) {
      res *= calculate(*item, root);
    }
    return res;
  }
}
