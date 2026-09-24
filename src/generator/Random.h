#ifndef EQUATION_GENERATOR_RANDOM_H
#define EQUATION_GENERATOR_RANDOM_H
#include <algorithm>
#include <random>

#include "ImplSettings.h"
#include "../nodes/NodeType.h"
#include "../../include/equation-generator/Settings.h"

namespace equation_generator {
  class Random {
  public:
    std::mt19937 engine;
    const ImplSettings& implSettings;
    const unsigned seed;

    explicit Random(const ImplSettings& implSettings):
    engine(implSettings.seed),
    implSettings(implSettings),
    seed(implSettings.seed)
    {}

    int getInt(int min, int max);
    float getFloat();
    bool getBool(float probability);
    float getValue(int depth = 1, int width = 1);
    float getRoot();
    float getPower();
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
