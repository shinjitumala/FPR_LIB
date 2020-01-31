#include <FPR/debug/level.h>

#include <iomanip>
#include <iostream>
#include <ostream>
#include <type_traits>

namespace FPR {
template <class O>
struct is_ostreamable {
    template <class T>
    static auto check(int) -> decltype(std::declval<std::ostream &>() << std::declval<T>(), std::true_type());
    template <class>
    static auto check(...) -> std::false_type;

  public:
    static constexpr bool value{std::is_same_v<decltype(check<O>(0)), std::true_type>};
};

/** Used to change color of std::ostream (ANSI) */
struct ANSI_State {
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
        UNDERLINE = 4,
        INVERSE = 7,
        BOLD_OFF = 21,
        UNDERLINE_OFF = 24,
        INVERSE_OFF = 27,
        NONE,
    };

    /** Background */
    Color bg;
    /** Foreground */
    Color fg;
    /** Emphasis (Bold, Underline, etc...) */
    Emphasis e;
};

/**
 * Custom overload used for colored terminal output (ANSI)
 * @param state New State
 * @return std::ostream& Destination
 */
std::ostream &operator<<(std::ostream &os, const ANSI_State &state);

constexpr ANSI_State ANSI_Reset{};
} // namespace FPR