#pragma once

#include <experimental/source_location>
#include <functional>

#include <FPR/debug/Logger.h>

namespace fpr {

constexpr auto msg = []() {
    return Logger(Logger::Level::MSG);
};
constexpr auto err = []() {
    return Logger(Logger::Level::ERR);
};
constexpr auto warn = []() {
    return Logger(Logger::Level::WARN);
};

constexpr auto info = []() {
    return Logger(Logger::Level::INFO);
};
constexpr auto red = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::RED);
};
constexpr auto grn = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::GREEN);
};
constexpr auto yel = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::YELLOW);
};
constexpr auto blu = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::BLUE);
};
constexpr auto mag = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::MAGENTA);
};
constexpr auto cyn = []() {
    return Logger(Logger::Level::INFO, ANSI_Out::State::Color::CYAN);
};

/**
 * Assert that does not use the pre processor.
 * @param condition Program will crash if this is not true.
 * @param failure Actions to take before crashing. Defaults to 'Do nothing'.
 * @param loc Source location to be displayed if the assertion fails.
 */
inline void asrt( bool &&condition, std::function<void()> failure = []() {},
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

        fpr::err() << ">> Assertion failed. Location: " << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " " << loc.function_name() << "\n";
        failure();
        fpr::err() << "<< Goodbye!" << reset() << std::endl;

        asm("INT3");
    }
}

/**
 * Executes 'warning' if the condition is not met.
 * @param condition Condition to execute 'warning'.
 * @param warning Fuction to be ececuted if 'condition' is false.
 * @param loc Source location to be displayed if 'condition' is false.
 */
inline void wasrt(
    bool &&condition, std::function<void()> warning = []() {},
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

        fpr::warn() << ">> Warning. Location: " << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " " << loc.function_name() << "\n";
        warning();
        fpr::warn() << "<<" << reset() << std::endl;
    }
}

constexpr auto ui = []() {
    Logger::indent_level++;
};
constexpr auto di = [](std::experimental::source_location loc = std::experimental::source_location::current()) {
    fpr::asrt(Logger::indent_level > 0, []() {
        fpr::err() << "Negative indent!\n";
    });
    Logger::indent_level--;
};
} // namespace fpr