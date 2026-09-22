#ifndef EQUATION_GENERATOR_H
#define EQUATION_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct eq_generator eq_generator;

eq_generator* eq_generator_create(void);
void eq_generator_destroy(eq_generator* generator);

#ifdef __cplusplus
}
#endif

#endif
