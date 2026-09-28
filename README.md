# Equation Generator

A C++20 library for generating configurable mathematical equations.

## Features

* **Pleasant roots** - The library generates roots first, which means that they can be constrained to integers or multiples of a configurable base.
* **Configurability** - Every step of the generation process can be customized if you don't like the provided defaults.
* **Built-in difficulty scoring** - Generated equations include a score for convenient difficulty estimation.
* **Reproducible generation** - Configure the generator's random seed.
* **Multiple language interfaces** - Although the library is built primarily for C++, you can use the provided fully functional C# and Python wrappers, as well as the C API.

## Example results

The generator should theoretically be able to produce any equation expressible using the currently supported operations.

From something simple:
```text
-8x + x² + 12 = 0

roots: [6, 2]
score: 7.05
```

to considerably more involved:
```text
x² + 2x⁴ + 64 - 16x + 2x³ = (x² + x) * 2x²

roots: [8, 8]
score: 10.56
```

The exact output is stochastic and depends on the configured settings and seed.

## Configuration

The generator is configured through `Settings`. All settings have defaults, so only the parameters relevant to a particular use case have to be specified.

### Values

Regular values, roots, and powers can be configured independently.

Each provides controls for:

| Setting          | Description                                 |
| ---------------- | ------------------------------------------- |
| `max`            | Target upper bound for generated values     |
| `lowBias`        | Bias towards smaller values; `1` is neutral |
| `negativeChance` | Probability of generating a negative value  |

#### Defaults

| Parameter | `max` | `lowBias` | `negativeChance` |
| --------- | ----: | --------: | ---------------: |
| values    |    20 |         2 |              0.3 |
| roots     |    10 |         1 |              0.3 |
| powers    |     2 |         1 |                0 |

*`max` is currently a target rather than a strict limit.*

### Expression structure

Several parameters influence the structure of generated expressions:

| Setting           | Description                                                                     | Default |
| ----------------- | ------------------------------------------------------------------------------- | ------: |
| `maxDepth`        | Maximum depth of multiplication chains                                          |       3 |
| `maxWidth`        | Maximum width of addition chains                                                |       4 |
| `valueChance`     | Probability that a branch terminates with a value rather than another operation |     0.3 |
| `rightSideChance` | Probability of placing an operand on the right-hand side of the equation        |     0.2 |

For example:

```text
x * x * y
```
has a depth of 3 (width 1), while:

```text
x + x + x + x
```
has a width of 4 (depth 1).

### Operations

Operations have configurable weights.
An operation with a higher weight is selected more frequently, while setting its weight to `0` removes it entirely.

The current version supports addition and multiplication. More operations will be introduced in the future.
The architecture is designed to allow further operations to be added without changing the core generator interface.

#### Defaults
| Operation      | Weight |
| -------------- | -----: |
| addition       |      2 |
| multiplication |      1 |

### Other settings

The generator also supports:

* equation degree (default: `2`)
* custom variable names (default: `x`)
* random seed (defaults: `std::random_device` for C++, C, and Python, `Guid.NewGuid().GetHashCode()` for C#)

## Difficulty score
Every generated equation includes a difficulty score. It is tuned to reflect the perceived difficulty of an equation based on factors such as its structure and the magnitude of its values.

## C++ usage

The primary API is exposed through the `include` directory.

A minimal example:

```cpp
#include <equation-generator/...>

#include <iostream>

void example()
{
  const Settings settings {
      .degree = 2,
  };
  Generator generator(settings);
  const Equation equation = generator.generate();

  std::cout << equation.str << '\n';
  std::cout << "roots: ";
  for (const auto root : equation.roots) {
      std::cout << root << ' ';
  }
  std::cout << "\nscore: " << equation.score << '\n';
}
```

### Public types

### `Settings`, `ValueSettings`, `StructureSettings`
Controls the behaviour of the generator.

```cpp
struct ValueSettings {
  struct Item {
    int max;
    float lowBias;
    float negativeChance;
  };
  float base = 1;
  Item values = Item{.max = 20, .lowBias = 2, .negativeChance = 0.3};
  Item roots = Item{.max = 10, .lowBias = 1, .negativeChance = 0.3};
  Item powers = Item{.max = 2, .lowBias = 1, .negativeChance = 0};
};
struct StructureSettings {
  struct OperationWeights {
    int add;
    int mult;
  };
  int maxDepth = 3;
  int maxWidth = 4;
  float valueChance = 0.3;
  float rightSideChance = 0.2;
  OperationWeights operationWeights = OperationWeights{.add = 2, .mult = 1};
};
struct Settings {
  unsigned seed = std::random_device{}();
  std::string variableName = "x";
  int degree = 2;
  ValueSettings valueSettings = ValueSettings{};
  StructureSettings structureSettings = StructureSettings{};
};
```

### `Equation`
Represents a generated equation:

```cpp
struct Equation {
  std::string str;
  std::vector<float> roots;
  float score;
};
```

* `str` - formatted equation
* `roots` - roots
* `score` - estimated difficulty

### `Generator`

Creates equations according to a `Settings` object:

```cpp
Generator(const Settings& settings);
[[nodiscard]] Equation generate() const;
```

## Other languages

The library provides C, C#, and Python interfaces.

### C

The C API is available through:

```text
include/c/equation_generator.h
```

Example:

```cpp
auto settings = eq_settings();
eq_set_defaults(&settings);

auto equation = eq_equation();

auto* generator = eq_generator_create(&settings);
eq_generator_generate(generator, &equation);

std::cout << equation.str << '\n';

eq_generator_destroy(generator);
eq_equation_destroy(&equation);
```

The C API exposes the core functionality through a C-compatible interface. It intentionally has fewer convenience features in order to reduce complexity.

### Python

The Python bindings are implemented using [pybind11](https://github.com/pybind/pybind11).

```python
import eqgen

settings = eqgen.Settings()
generator = eqgen.Generator(settings)
equation = generator.generate()

print(equation.str)
print(equation.roots)
print(equation.score)
```

### C#

```csharp
var settings = new gen.Settings();
var generator = new gen.Generator(settings);
var equation = generator.Generate();

Console.WriteLine(equation.Str);
foreach (var root in equation.Roots)
{
  Console.WriteLine(root);
}
Console.WriteLine(equation.Score);
```

## Building

The project uses **CMake** and **C++20**.

The project is currently developed on Windows using MSVC. Linux and other compilers *could* work, but haven't been tested.

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Python bindings

The Python bindings require [pybind11](https://github.com/pybind/pybind11).

Python bindings can be enabled through the CMake configuration:

```bash
cmake -S . -B build -DBUILD_PYTHON=ON
cmake --build build
```

## Current limitations

The generator is functional, but some of its configuration parameters are currently heuristic rather than strict guarantees.

### Value upper bounds

`max` settings generally keep generated values under the requested limit, but do not currently guarantee it.

### Generated complexity

To guarantee the mathematical validity of an equation with predefined roots, the generator first constructs the base polynomial corresponding to those roots. Additional terms are then introduced in a way that preserves those roots.

Because these terms are randomly generated, they can sometimes simplify against each other.

This can result in an equation that is stripped down to its base polynomial. It is mathematically valid, but lacks the structural complexity that the input parameters might suggest.

Tweaking structural settings may reduce this effect, but it can also cause successful generations to "blow up".

To ensure sufficient difficulty, iterative generation is recommended. The library intentionally omits this approach in order to keep the generation algorithm as lightweight as possible.

## Planned features and improvements

* improve structural complexity control and make it more intuitive
* make the C API more closely match the native C++ API
* add an option to generate equations from user-defined roots
* make value limits strict rather than targets
* reduce cancellation of generated complexity
* add more mathematical operations
