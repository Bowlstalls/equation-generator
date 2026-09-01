#include "random.h"

#include <algorithm>
#include <stdexcept>

using namespace equation_generator;

int Random::getInt(const int min, const int max)
{
  std::uniform_int_distribution distribution(min, max);
  return distribution(engine);
}

float Random::getFloat()
{
  std::uniform_real_distribution<float> distribution(0, 1);
  return distribution(engine);
}

bool Random::getBool(const float probability)
{
  std::bernoulli_distribution distribution(probability);
  return distribution(engine);
}

int Random::getValue()
{
  return getInt(settings.values);
}

int Random::getRoot()
{
  return getInt(settings.roots);
}

int Random::getPower()
{
  return getInt(settings.powers);
}

int Random::choose(const std::vector<int>& weights)
{
  int sum = 0;
  for (auto& weight : weights) {
    sum += weight;
  }
  auto res = getInt(0, sum - 1);
  const auto ineedthat = res;
  for (auto i = 0; i < weights.size(); ++i) {
    res -= weights[i];
    if (res < 0) {
      return i;
    }
  }
  throw std::logic_error("Unreachable");
}

NodeType Random::getOperation()
{
  std::vector<NodeType> keys;
  std::vector<int> values;
  for (auto& [fst, snd] : settings.typeWeights) {
    keys.push_back(fst);
    values.push_back(snd);
  }
  return keys.at(choose(values));
}

template<typename T>
void Random::shuffle(std::vector<T>& list)
{
  std::ranges::shuffle(list, engine);
}

int Random::getInt(const Settings::ValueSettings params)
{
  float raw = std::pow(getFloat(), params.lowBias) * static_cast<float>(params.max);
  if (getBool(params.negativeChance)) {
    raw *= -1;
  }
  return static_cast<int>(std::round(raw));
}
