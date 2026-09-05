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

float Random::getValue(const int depth, const int width)
{
  const auto& [max, lowBias, negativeChance] = settings.valueSettings.values;
  float res = getInt(1, max, lowBias);
  res = std::pow(res, 1.0 / depth) / width;
  if (getBool(negativeChance)) {
    res *= -1;
  }
  return res;
}

float Random::getRoot()
{
  return getInt(1, settings.valueSettings.roots);
}

float Random::getPower(const int depth)
{
  const auto& [max, lowBias, negativeChance] = settings.valueSettings.powers;
  float res = getInt(1, max, lowBias);
  res = std::round(res / depth);
  if (getBool(negativeChance)) {
    res *= -1;
  }
  return res;
}

int Random::choose(const std::vector<int>& weights)
{
  int sum = 0;
  for (auto& weight : weights) {
    sum += weight;
  }
  auto res = getInt(0, sum - 1);
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
  for (const auto& [fst, snd] : settings.structureSettings.operationWeights) {
    keys.push_back(fst);
    values.push_back(snd);
  }
  return keys.at(choose(values));
}

int Random::getInt(const int min, const int max, const float lowBias)
{
  return min + getFloat(lowBias) * (max - min);
}

float Random::getFloat(const float lowBias)
{
  return std::pow(getFloat(), lowBias);
}

int Random::getInt(const int min, const ValueSettings::Item& preset)
{
  int res = getInt(min, preset.max, preset.lowBias);
  if (getBool(preset.negativeChance)) {
    res *= -1;
  }
  return res;
}
