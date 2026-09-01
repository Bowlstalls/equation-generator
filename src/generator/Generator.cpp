#include "Generator.h"

#include "Expression.h"
#include "../nodes/ValueNode.h"
#include "../nodes/operations/AddNode.h"

using namespace equation_generator;

Generator::Generator(const Settings& settings):
settings(settings),
random(Random(std::random_device{}(), settings)),
nodeGenerator(NodeGenerator(*this)),
nodeOptimizer(NodeOptimizer(*this))
{}

static std::vector<int> getCoefficients(const std::vector<int>& roots)
{
  std::vector<int> out(roots.size());
  for (size_t i = 0; i < roots.size(); ++i) {
    for (size_t j = i; j > 0; --j) {
      out[j] += roots[i] * out[j - 1];
    }
    out[0] += roots[i];
  }
  return out;
}

static AddNode getRootPolynomial(const std::vector<int>& roots, const std::string& name = "x")
{
  AddNode res;
  auto& list = res.list;
  const size_t len = roots.size();
  const auto coefficients = getCoefficients(roots);
  auto sign = -1;
  auto power = len - 1;

  list.push_back(std::make_unique<ValueNode>(name, 1, len));
  for (auto i = 0; i < len; ++i) {
    list.push_back(std::make_unique<ValueNode>(name, coefficients[i] * sign, power));
    power--;
    sign *= -1;
  }
  return res;
}

Expression Generator::generate(int targetScore)
{

}
