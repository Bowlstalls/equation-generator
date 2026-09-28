#include <iostream>

#include <equation-generator/Generator.h>
#include "../include/equation-generator/Settings.h"
#include <equation-generator/c/equation_generator.h>

using namespace equation_generator;

void cpp()
{
  const Settings settings {
    .degree = 2,
  };

  Generator generator(settings);
  const Equation res = generator.generate();
  std::cout << res.str << "\n";
  std::cout << "roots: " << "\n";
  for (const auto root : res.roots) {
    std::cout << root << " ";
  }
  std::cout << "\nscore: " << res.score;
}

void c()
{
  auto settings = eq_settings();
  eq_set_defaults(&settings);
  auto res = eq_equation();
  auto* generator = eq_generator_create(&settings);
  eq_generator_generate(generator, &res);

  std::cout << res.str << "\n";
  std::cout << "roots: " << "\n";
  for (size_t i = 0; i < res.root_count; i++) {
    std::cout << res.roots[i] << " ";
  }
  std::cout << "\nscore: " << res.score;

  eq_generator_destroy(generator);
  eq_equation_destroy(&res);
}

int main()
{
  c();
  cpp();
};
