#include "Expression.h"

#include "nodes/AddNode.h"
#include "nodes/MultNode.h"
#include "nodes/VarNode.h"
using namespace equation_generator;

Expression::Expression(const std::vector<int>& roots): roots{roots}
{
  const auto x = std::make_unique<VarNode>("x", 1, 1);
  std::vector<std::unique_ptr<Node>> list;
  for (const auto root : roots) {
    list.push_back(std::make_unique<AddNode>(x->clone(), std::make_unique<ValueNode>(-root)));
  }
  if (list.size() == 1) {
    lhs = std::move(list[0]);
  } else {
    lhs = std::make_unique<MultNode>(std::move(list));
  }
  rhs = std::make_unique<ValueNode>(0);
}

void Expression::mutate(GeneratorParams& params)
{
  lhs = lhs->mutate(std::move(lhs), params);
  rhs = rhs->mutate(std::move(rhs), params);
}

std::string Expression::toString() const
{
  return lhs->toString() + " = " + rhs->toString();
}
