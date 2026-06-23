#ifndef GENERATOR_H
#define GENERATOR_H
#include <random>

namespace equation_generator {
  struct GeneratorParams {
    struct ValueParams {
      int max;
      float lowBias;
      float negativeChance;
    };

    std::mt19937 generator;
    float mutationChance;
    ValueParams values;
    ValueParams roots;

    GeneratorParams(const float mutationChance, const ValueParams values, const ValueParams roots):
    mutationChance(mutationChance),
    values(values),
    roots(roots)
    {
      std::random_device rd;
      generator = std::mt19937(rd());
    }
    bool doMutate()
    {
      return getRandomBool(mutationChance);
    }
    int getRandomInt(const int min, const int max)
    {
      std::uniform_int_distribution distribution(min, max);
      return distribution(generator);
    }
    int getRandomValue()
    {
      return getRandomInt(values);
    }
    int getRandomRoot()
    {
      return getRandomInt(roots);
    }

  private:
    int getRandomInt(const ValueParams params)
    {
      std::uniform_real_distribution<float> distribution(0, 1);
      float raw = std::pow(distribution(generator), params.lowBias) * params.max;
      if (getRandomBool(params.negativeChance)) {
        raw *= -1;
      }
      return std::round(raw);
    }
    bool getRandomBool(const float probability)
    {
      std::bernoulli_distribution distribution(probability);
      return distribution(generator);
    }
  };

  class Generator {

  };
}



#endif
