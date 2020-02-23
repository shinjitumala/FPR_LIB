#pragma once

#include <ostream>

namespace fpr {
/** Used to print ANSI escape code to decorate terminal output. */
struct ansicc {
    /** Foreground Color code. Add 10 to convert to backgroudn color code. */
    enum class Color {
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

    /** Emphasis (Bold, Underline, etc...) */
    enum class Emphasis {
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

    /** Background */
    Color bg;
    /** Foreground */
    Color fg;
    /** Emphasis (Bold, Underline, etc...) */
    Emphasis e;

    /** Default constructor: Resets terminal color */
    ansicc();
    /**
     * @param bg 
     * @param fg 
     * @param e 
     */
    ansicc(Color bg, Color fg, Emphasis e);
};
} // namespace fpr

/**
 * Operator overload for ansicc
 * @param os 
 * @param cc 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &os, fpr::ansicc cc);