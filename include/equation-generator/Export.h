#ifndef EQUATION_GENERATOR_EXPORT_H
#define EQUATION_GENERATOR_EXPORT_H

#if defined(_WIN32)

    #ifdef EQUATION_GENERATOR_BUILD
        #define EQUATION_GENERATOR_API __declspec(dllexport)
    #else
        #define EQUATION_GENERATOR_API __declspec(dllimport)
    #endif

#elif defined(__GNUC__) || defined(__clang__)

    #define EQUATION_GENERATOR_API __attribute__((visibility("default")))

#else

    #define EQUATION_GENERATOR_API

#endif

#endif
