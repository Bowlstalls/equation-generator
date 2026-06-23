#include <iostream>

#include "../src/Expression.h"
using namespace equation_generator;

int main()
{
  GeneratorParams params(1, {5, 2, 0}, {1, 1, 1});
  Expression expr(std::vector{2, 4});
  std::cout << "Initial: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "One pass: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "Two pass: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "Three pass: " << expr.toString() << "\n";
  expr.mutate(params);
  std::cout << "Four pass: " << expr.toString() << "\n";
}
