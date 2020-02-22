#pragma once

#include <experimental/source_location>
#include <functional>

#include <FPR/debug/Logger.h>
#include <string>

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

constexpr auto info = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG);
    } else {
        return Logger(Logger::Level::INFO);
    }
};
constexpr auto red = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::RED);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::RED);
    }
};
constexpr auto grn = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::GREEN);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::GREEN);
    }
};
constexpr auto yel = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::YELLOW);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::YELLOW);
    }
};
constexpr auto blu = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::BLUE);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::BLUE);
    }
};
constexpr auto mag = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::MAGENTA);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::MAGENTA);
    }
};
constexpr auto cyn = [](const bool msg = false) {
    if (msg) {
        return Logger(Logger::Level::MSG, ANSI_Out::State::Color::CYAN);
    } else {
        return Logger(Logger::Level::INFO, ANSI_Out::State::Color::CYAN);
    }
};

constexpr auto print_location = [](const std::experimental::source_location &loc) -> std::string {
    std::string s;
    s += "Location: ";
    s += loc.file_name();
    s += ":";
    s += std::to_string(loc.line());
    s += ":";
    s += std::to_string(loc.column());
    s += " ";
    s += loc.function_name();
    s += "()\n";
    return s;
};

/**
 * Assert that does not use the pre processor.
 * @param condition Program will crash if this is not true.
 * @param failure Actions to take before crashing. Defaults to 'Do nothing'.
 * @param loc Source location to be displayed if the assertion fails.
 */
inline void asrt(
    bool &&condition, std::function<void()> failure = []() {},
    const std::experimental::source_location &loc = std::experimental::source_location::current()) {
#ifdef NDEBUG
    static const bool debug{false};
#else
    static const bool debug{true};
#endif

    if constexpr (debug) {
        if (condition) {
            return;
        }

        fpr::err() << ">> Assertion failed. " << print_location(loc);
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
    const std::experimental::source_location &loc =
        std::experimental::source_location::current()) {
#ifdef NDEBUG
    static const bool debug{false};
#else
    static const bool debug{true};
#endif

    if constexpr (debug) {
        if (condition) {
            return;
        }

        fpr::warn() << ">> Warning. " << print_location(loc);
        warning();
        fpr::warn() << "<<" << reset() << std::endl;
    }
}

constexpr auto ui = []() {
    Logger::indent_level++;
};
constexpr auto di = [](const std::experimental::source_location &loc = std::experimental::source_location::current()) {
    fpr::asrt(
        Logger::indent_level > 0,
        []() {
            fpr::err() << "Negative indent!\n";
        });
    Logger::indent_level--;
};
} // namespace fpr