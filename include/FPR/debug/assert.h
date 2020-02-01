#pragma once

#include <experimental/source_location>
#include <functional>

#include <FPR/out/ansi_out.h>

namespace fpr {
/**
 * Assert that does not use the pre processor.
 * @param condition Program will crash if this is not true.
 * @param failure Actions to take before crashing. Defaults to 'Do nothing'.
 * @param loc Source location to be displayed if the assertion fails.
 */
inline void asrt(
    bool &&condition,
    std::function<void()> failure = []() {},
    std::experimental::source_location loc = std::experimental::source_location::current()) {
#ifdef DEBUG
    static const bool debug{true};
#else
    static const bool debug{false};
#endif

    if constexpr (debug) {
        if (condition) {
            return;
        }

        ANSI_Out{std::cerr} << ANSI_Out::State{
                                   .bg = ANSI_Out::State::Color::BLACK,
                                   .fg = ANSI_Out::State::Color::RED,
                                   .e = ANSI_Out::State::Emphasis::BOLD}
                            << ">> Assertion failed. Location: " << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " " << loc.function_name() << "\n";
        failure();
        ANSI_Out{std::cerr} << ANSI_Out::State{
                                   .bg = ANSI_Out::State::Color::BLACK,
                                   .fg = ANSI_Out::State::Color::RED,
                                   .e = ANSI_Out::State::Emphasis::BOLD}
                            << "\n<< Goodbye!" << std::endl;

        asm("INT3");
    }
}

/**
 * Executes 'warning' if the condition is not met.
 * @param condition Condition to execute 'warning'.
 * @param warning Fuction to be ececuted if 'condition' is false.
 * @param loc Source location to be displayed if 'condition' is false.
 */
inline void warn(
    bool &&condition,
    std::function<void()> warning = []() {},
    std::experimental::source_location loc =
        std::experimental::source_location::current()) {
#ifdef DEBUG
#undef DEBUG
    static const bool debug{true};
#else
    static const bool debug{false};
#endif

    if constexpr (debug) {
        if (condition) {
            return;
        }

        ANSI_Out{std::cerr} << ANSI_Out::State{
                                   .bg = ANSI_Out::State::Color::BLACK,
                                   .fg = ANSI_Out::State::Color::YELLOW,
                                   .e = ANSI_Out::State::Emphasis::BOLD}
                            << ">> Warning. Location: " << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " " << loc.function_name() << "\n";
        warning();
        ANSI_Out{std::cerr} << ANSI_Out::State{
                                   .bg = ANSI_Out::State::Color::BLACK,
                                   .fg = ANSI_Out::State::Color::YELLOW,
                                   .e = ANSI_Out::State::Emphasis::BOLD}
                            << "\n<<" << std::endl;
    }
}
} // namespace fpr