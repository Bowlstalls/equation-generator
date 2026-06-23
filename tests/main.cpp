#include <iostream>

#include "../src/nodes/AddNode.h"
#include "../src/nodes/MultNode.h"
#include "../src/nodes/ValueNode.h"
#include "../src/nodes/VarNode.h"
using namespace equation_generator;

int main()
{
  auto left = std::make_unique<AddNode>(std::make_unique<VarNode>("x", 1, 1), std::make_unique<ValueNode>(2));
  auto right = std::make_unique<AddNode>(std::make_unique<VarNode>("x", 1, 1), std::make_unique<ValueNode>(4));
  std::unique_ptr<Node> mult = std::make_unique<MultNode>(std::move(left), std::move(right));
  GeneratorParams params(1, {5, 2, 0}, {1, 1, 1});
  mult = mult->mutate(std::move(mult), params);
  std::cout << mult->toString();
}
