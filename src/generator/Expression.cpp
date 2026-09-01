#include "Expression.h"

#include "../nodes/operations/AddNode.h"
#include "../nodes/operations/MultNode.h"
using namespace equation_generator;

std::string Expression::toString() const
{
  return lhs->toString() + " = " + rhs->toString();
}
