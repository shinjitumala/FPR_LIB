#pragma once

#include <iostream>
#include <ostream>

namespace fpr {
using namespace std;

/// Used to print ANSI escape code to decorate terminal output.
namespace ansicc {
/// Foreground Color code. Add 10 to convert to backgroudn color code.
enum class Color
{
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    NONE,
};

/// Emphasis (Bold, Underline, etc...)
enum class Emphasis
{
    RESET = 0,
    BOLD = 1,
    FAINT = 2,
    ITALIC = 3,
    UNDERLINE = 4,
    SLOW_BLINK = 5,
    FAST_BLINK = 6,
    INVERSE = 7,
    CONCEAL = 8,
    CROSS_OUT = 9,
    BOLD_OFF = 21,
    UNDERLINE_OFF = 24,
    INVERSE_OFF = 27,
    FRAMED = 51,
    NONE,
};

template<Color fg, Color bg, Emphasis e>
struct Colorizer
{
    static bool should_print() { return true; }
    static ostream& get_os() { return cout; }
    static void prefix(ostream& os)
    {
        os << "\x1b["; // Escape Character
        bool flag{ false };
        if (fg != fpr::ansicc::Color::NONE) {
            os << static_cast<uint>(fg);
            flag = true;
        }
        if (bg != fpr::ansicc::Color::NONE) {
            if (flag) {
                os << ";";
            }
            os << static_cast<uint>(bg) + 10;
            flag = true;
        }
        if (e != fpr::ansicc::Emphasis::NONE) {
            if (flag) {
                os << ";";
            }
            os << static_cast<uint>(e);
        }
        os << "m"; // End
    }
    static void postfix(ostream& os)
    {
        os << "\x1b[0m"; // Reset
    }
};

// Some preset colors
using Red = Colorizer<Color::RED, Color::NONE, Emphasis::NONE>;
using Green = Colorizer<Color::GREEN, Color::NONE, Emphasis::NONE>;
using Yellow = Colorizer<Color::YELLOW, Color::NONE, Emphasis::NONE>;
using Blue = Colorizer<Color::BLUE, Color::NONE, Emphasis::NONE>;
using Magenta = Colorizer<Color::MAGENTA, Color::NONE, Emphasis::NONE>;
using Cyan = Colorizer<Color::CYAN, Color::NONE, Emphasis::NONE>;
}
}