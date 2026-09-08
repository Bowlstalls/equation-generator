#ifndef EQUATION_GENERATOR_EQUATIONVERIFIER_H
#define EQUATION_GENERATOR_EQUATIONVERIFIER_H
#include <map>

#include "../../include/equation-generator/Equation.h"

namespace equation_generator {
  class EquationVerifier {
  public:
    static bool verify(const Equation& equation);

  private:
    static int calculate(const Node& node, int root);

    static int calculateValueNode(const Node& node, int root);
    static int calculateAddNode(const Node& node, int root);
    static int calculateMultNode(const Node& node, int root);

    inline static std::map<NodeType, int(*)(const Node&, int)> typeMap {
      {NodeType::ValueNode, calculateValueNode},
      {NodeType::AddNode, calculateAddNode},
      {NodeType::MultNode, calculateMultNode}
    };
  };
}

#endif
