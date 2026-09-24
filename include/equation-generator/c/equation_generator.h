#ifndef EQUATION_GENERATOR_H
#define EQUATION_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int max;
  float low_bias;
  float negative_chance;
} eq_value_settings_item;

typedef struct {
  float base;
  eq_value_settings_item values;
  eq_value_settings_item roots;
  eq_value_settings_item powers;
} eq_value_settings;

typedef struct {
  int add;
  int mult;
} eq_operation_weights;

typedef struct {
  int max_depth;
  int max_width;
  float value_chance;
  float right_side_chance;
  eq_operation_weights operation_weights;
} eq_structure_settings;

typedef struct {
  unsigned seed;
  const char *variable_name;
  int degree;
  eq_value_settings value_settings;
  eq_structure_settings structure_settings;
} eq_settings;

typedef struct eq_generator eq_generator;

eq_generator* eq_generator_create(void);
void eq_generator_destroy(eq_generator* generator);

#ifdef __cplusplus
}
#endif

#endif
