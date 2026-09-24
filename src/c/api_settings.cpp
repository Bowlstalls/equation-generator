#include "api_settings.h"

static equation_generator::Settings convert_settings(const eq_settings& settings)
{
  equation_generator::Settings res;

  res.seed = settings.seed;
  res.variableName = settings.variable_name;
  res.degree = settings.degree;

  res.valueSettings.base = settings.value_settings.base;

  res.valueSettings.values.max =
      settings.value_settings.values.max;
  res.valueSettings.values.lowBias =
      settings.value_settings.values.low_bias;
  res.valueSettings.values.negativeChance =
      settings.value_settings.values.negative_chance;

  res.valueSettings.roots.max =
      settings.value_settings.roots.max;
  res.valueSettings.roots.lowBias =
      settings.value_settings.roots.low_bias;
  res.valueSettings.roots.negativeChance =
      settings.value_settings.roots.negative_chance;

  res.valueSettings.powers.max =
      settings.value_settings.powers.max;
  res.valueSettings.powers.lowBias =
      settings.value_settings.powers.low_bias;
  res.valueSettings.powers.negativeChance =
      settings.value_settings.powers.negative_chance;

  res.structureSettings.maxDepth =
      settings.structure_settings.max_depth;
  res.structureSettings.maxWidth =
      settings.structure_settings.max_width;
  res.structureSettings.valueChance =
      settings.structure_settings.value_chance;
  res.structureSettings.rightSideChance =
      settings.structure_settings.right_side_chance;

  res.structureSettings.operation_weights.add =
      settings.structure_settings.operation_weights.add;
  res.structureSettings.operation_weights.mult =
      settings.structure_settings.operation_weights.mult;

  return res;
}
