#include <iostream>

#include "../src/Expression.h"
using namespace equation_generator;

int main()
{
  GeneratorParams params(1, {5, 1.5, 0}, {1, 1, 1});
  Expression expr(std::vector{1});
  std::cout << "Initial: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "First Pass: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "Second Pass: " << expr.toString() << "\n";
  expr.mutate(params);
}
