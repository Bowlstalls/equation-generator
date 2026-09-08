#include "../../include/equation-generator/Generator.h"

#include "../../include/equation-generator/Equation.h"
#include "../nodes/Node.h"
#include "../nodes/ValueNode.h"
#include "../nodes/operations/AddNode.h"
#include "inspectors/EquationScorer.h"
#include "operators/NodeFlattener.h"

using namespace equation_generator;

Generator::Generator(const Settings& settings):
settings(settings),
random(Random( settings)),
nodeGenerator(random, settings),
nodeOptimizer(random, settings)
{}

Equation Generator::generate()
{
  Equation res = getRootEquation(settings.degree);
  std::unique_ptr<Node> posTerm = nodeOptimizer.optimize(nodeGenerator.generateOperation());

  auto total = std::make_unique<AddNode>();
  total->addItem(std::move(res.lhs));
  if (posTerm) {
    posTerm->setBase(settings.valueSettings.base);
    total->addItem(std::move(posTerm->clone()));
    std::unique_ptr<Node> negTerm = NodeFlattener::flatten(std::move(posTerm));
    negTerm->negate();
    total->addItem(std::move(negTerm));
  }

  res.lhs = nodeOptimizer.optimize(std::move(total));
  res.score = EquationScorer::score(res);
  spill(res);
  return res;
}

static std::vector<float> getCoefficients(const std::vector<float>& roots)
{
  std::vector<float> out(roots.size());
  for (size_t i = 0; i < roots.size(); ++i) {
    for (size_t j = i; j > 0; --j) {
      out[j] += roots[i] * out[j - 1];
    }
    out[0] += roots[i];
  }
  return out;
}

static std::unique_ptr<Node> getRootPolynomial(const std::vector<float>& roots, std::string variableName)
{
  std::vector<std::unique_ptr<Node>> list;
  const size_t len = roots.size();
  const auto coefficients = getCoefficients(roots);
  auto sign = -1;
  auto power = len - 1;

  list.push_back(std::make_unique<ValueNode>(variableName, 1, len));
  for (auto i = 0; i < len; ++i) {
    list.push_back(std::make_unique<ValueNode>(variableName, coefficients[i] * sign, power));
    power--;
    sign *= -1;
  }
  return std::make_unique<AddNode>(std::move(list));
}

Equation Generator::getRootEquation(const int degree) {
  std::vector<float> roots;
  for (auto i = 0; i < degree; ++i) {
    roots.push_back(random.getRoot());
  }
  return Equation {
    .roots = roots,
    .lhs = getRootPolynomial(roots, settings.variableName)
  };
}

void Generator::spill(Equation& equation)
{
  auto* lhs = dynamic_cast<AddNode*>(&*equation.lhs);
  if (!lhs) {
    return;
  }
  std::vector<std::unique_ptr<Node>> lhsList;
  std::vector<std::unique_ptr<Node>> rhsList;

  for (auto& item : lhs->list) {
    if (random.getBool(settings.structureSettings.rightSideChance)) {
      item->negate();
      rhsList.push_back(std::move(item));
    } else {
      lhsList.push_back(std::move(item));
    }
  }
  lhs->list = std::move(lhsList);
  if (rhsList.size() == 0) {
    equation.rhs = std::make_unique<ValueNode>(0);
    return;
  }
  if (rhsList.size() == 1) {
    equation.rhs = std::move(rhsList[0]);
    return;
  }
  equation.rhs = std::make_unique<AddNode>(std::move(rhsList));
}
