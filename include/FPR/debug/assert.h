#pragma once

#include <cstdlib>
#include <experimental/source_location>
#include <iostream>
#include <string>

namespace fpr {
/**
 * @param loc Source code location
 * @return const std::string FPR's string representation of the location
 */
constexpr auto print_location = [](const std::experimental::source_location loc) -> const std::string {
    std::string s;
    s += "Location: ";
    s += loc.file_name();
    s += ":";
    s += std::to_string(loc.line());
    s += ":";
    s += std::to_string(loc.column());
    s += " ";
    s += loc.function_name();
    s += "()";
    return s;
};

/**
 * FPR's convenient assert
 * @param condition Program will crash if this is not true.
 * @param action Code to be executed before crashing
 */
#ifndef NDEBUG
#define asrt(condition, action)                                         \
    if (!(condition)) {                                                 \
        err() << "Assertion Failure: " << #condition << "\n"        \
                  << fpr::print_location(                               \
                         std::experimental::source_location::current()) \
                  << std::endl;                                         \
        if constexpr (static_cast<bool>(sizeof(#action) - 1)) {         \
            action;                                                     \
            std::cerr << std::endl;                                     \
        }                                                               \
        ::abort();                                                      \
    }
#else
#define asrt(condition, action)
#endif

/**
 * Executes 'warning' if the condition is not met.
 * @param condition Condition to execute 'warning'.
 * @param warning Fuction to be ececuted if 'condition' is false.
 * @param loc Source location to be displayed if 'condition' is false.
 */
#ifndef NDEBUG
#define wsrt(condition, action)                                            \
    if (!(condition)) {                                                    \
        wrn() << "Assertion Failure (Warning): " << #condition << "\n" \
                  << fpr::print_location(                                  \
                         std::experimental::source_location::current())    \
                  << std::endl;                                            \
        if constexpr (static_cast<bool>(sizeof(#action) - 1)) {            \
            wrn() << "{\n";                                            \
            action;                                                        \
            wrn() << "\n}" << std::endl;                               \
        }                                                                  \
    }
#else
#define wsrt(condition, action)
#endif
} // namespace fpr
