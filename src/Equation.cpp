#include "Equation.h"

#include "../nodes/operations/AddNode.h"
#include "../nodes/operations/MultNode.h"
using namespace equation_generator;

std::string Equation::toString() const
{
  return lhs->toString() + " = " + rhs->toString();
}
