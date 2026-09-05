#ifndef EQUATION_GENERATOR_RANDOM_H
#define EQUATION_GENERATOR_RANDOM_H
#include <algorithm>
#include <random>

#include "../nodes/NodeType.h"
#include "settings.h"

namespace equation_generator {
  class Random {
  public:
    std::mt19937 engine;
    const Settings& settings;
    const unsigned seed;

    explicit Random(const Settings& settings):
    engine(settings.seed),
    settings(settings),
    seed(settings.seed)
    {}

    int getInt(int min, int max);
    float getFloat();
    bool getBool(float probability);
    int getValue();
    int getRoot();
    int getPower();
    int choose(const std::vector<int>& weights);
    NodeType getOperation();

    template<typename T>
    void shuffle(std::vector<T>& list)
    {
      std::ranges::shuffle(list, engine);
    }

  private:
    int getInt(int min, int max, float lowBias);
    int getInt(int min, const ValueSettings::Item& preset);
    float getFloat(float lowBias);
  };
}

#endif
