#ifndef EQUATION_GENERATOR_EQUATIONSCORER_H
#define EQUATION_GENERATOR_EQUATIONSCORER_H

#include <cmath>
#include <iostream>
#include <map>

#include "../EquationData.h"

namespace equation_generator {
  class EquationScorer {
  public:
    static float score(const EquationData& equation);

  private:
    inline static float degreeWeight = 1;

    struct Data {
      struct avg {
        float sum = 0;
        int count = 0;
        float weight;

        void add(const float value)
        {
          sum += value;
          ++count;
        }
        float getValue() const
        {
          return std::pow(sum / count, weight);
        }
      };
      avg depth{.weight = 2};
      avg width{.weight = 0.7};
      avg coefficientSize{.weight = 0.5};
      avg rootSize{.weight = 0.5};

      void setRoots(const std::vector<float>& roots)
      {
        for (const auto& root : roots) {
          rootSize.add(std::to_string(std::abs(root)).length());
        }
      }
      float getTotal() const
      {
        std::cout << "depth: " << depth.getValue() << '\n';
        std::cout << "width: " << width.getValue() << '\n';
        std::cout << "coefficientSize: " << coefficientSize.getValue() << '\n';
        std::cout << "rootSize: " << rootSize.getValue() << '\n';
        return depth.getValue() * width.getValue() * coefficientSize.getValue() * rootSize.getValue();
      }
    };

    static void score(const Node& node, Data& data, int depth = 1);

    static void scoreValueNode(const Node& node, Data& data, int depth);
    static void scoreAddNode(const Node& node, Data& data, int depth);
    static void scoreMultNode(const Node& node, Data& data, int depth);

    inline static std::map<NodeType, void(*)(const Node&, Data&, int)> typeMap {
      {NodeType::ValueNode, scoreValueNode},
      {NodeType::AddNode, scoreAddNode},
      {NodeType::MultNode, scoreMultNode}
    };
  };
}

#endif
