#ifndef EQUATION_GENERATOR_RANDOM_H
#define EQUATION_GENERATOR_RANDOM_H
#include <random>

#include "../nodes/NodeType.h"
#include "settings.h"

namespace equation_generator {
  class Random {
  public:
    std::mt19937 generator;
    Settings settings;

    Random(const unsigned seed, const Settings& settings): generator{seed}, settings{settings} {}

    int getInt(int min, int max);
    float getFloat();
    bool getBool(float probability);
    int getValue();
    int getRoot();
    int getPower();
    int choose(const std::vector<int>& weights);
    NodeType getOperation();

  private:
    int getInt(Settings::ValueSettings params);
  };
}

#endif
