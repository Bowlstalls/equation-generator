#ifndef EQUATION_GENERATOR_VALUENODE_H
#define EQUATION_GENERATOR_VALUENODE_H

#include "Node.h"

namespace equation_generator {
  class ValueNode final : public Node {
  public:
    float value;
    int power = 0;
    std::string name;

    explicit ValueNode(float value);
    explicit ValueNode(std::string name, float value = 1, int power = 0);

    ValueNode operator+(const ValueNode& other) const;
    ValueNode operator-(const ValueNode& other) const;
    ValueNode operator*(const ValueNode& other) const;
    void operator+=(const ValueNode& other);
    void operator-=(const ValueNode& other);
    void operator*=(const ValueNode& other);
    ValueNode operator-() const;

    void negate() override;
    void setBase(float base) override;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::unique_ptr<Node> clone() const override;
  };
}

#endif
