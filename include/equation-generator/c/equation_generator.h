#ifndef EQUATION_GENERATOR_H
#define EQUATION_GENERATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct eg_generator eg_generator;

typedef struct {
    int max;
    float low_bias;
    float negative_chance;
} eg_value_settings_item;

typedef struct {
    float base;
    eg_value_settings_item values;
    eg_value_settings_item roots;
    eg_value_settings_item powers;
} eg_value_settings;

typedef struct {
    int max_depth;
    int max_width;
    float value_chance;
    float right_side_chance;

    int add_weight;
    int mult_weight;
} eg_structure_settings;

typedef struct {
    uint32_t seed;
    const char* variable_name;
    int degree;
    eg_value_settings value_settings;
    eg_structure_settings structure_settings;
} eg_settings;

typedef struct {
    char* str;
    float* roots;
    int root_count;
    float score;
} eg_equation;

void eg_set_defaults(eg_settings *settings);

eg_generator *eg_generator_create(const eg_settings *settings);
void eg_generator_destroy(eg_generator *generator);


/*
 * Generate an equation.
 *
 * Returns 0 on success.
 * Returns non-zero on failure.
 *
 * On success, call eg_equation_free() when finished.
 */
int eg_generator_generate(
    eg_generator *generator,
    eg_equation *result
);


/*
 * Free an equation returned by eg_generator_generate().
 */
void eg_equation_free(eg_equation *equation);


/*
 * Get a description of the last error.
 *
 * The returned string is owned by the library.
 * Do not free it.
 */
const char *eg_last_error(void);


#ifdef __cplusplus
}
#endif

#endif
