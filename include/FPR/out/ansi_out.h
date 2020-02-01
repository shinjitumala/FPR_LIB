#pragma once

#include <iomanip>
#include <iostream>
#include <ostream>
#include <type_traits>

namespace fpr {
/**
 * 'value' is set to true iff O can be passed to a std::ostream.
 * @tparam O 
 */
template <class O>
struct is_ostreamable {
    template <class T>
    static auto check(int) -> decltype(std::declval<std::ostream &>() << std::declval<T>(), std::true_type());
    template <class>
    static auto check(...) -> std::false_type;

  public:
    static constexpr bool value{std::is_same_v<decltype(check<O>(0)), std::true_type>};
};

/** std::ostream wrapper for colored output. */
class ANSI_Out {
  protected:
    /** Output desitination */
    std::ostream &os;

  public:
    /** Used to change color of std::ostream (ANSI) */
    struct State {
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
     * @param os Output destination.
     */
    ANSI_Out(std::ostream &os = std::cout);
    /** Disallow copy */
    ANSI_Out(const ANSI_Out &) = delete;

    /**
     * @tparam O Type to be streamed.
     * @tparam std::enable_if_t<is_ostreamable<O>::value> Only enabled if operator exists.
     * @param o Value to be streamed.
     * @return ANSI_Out& YES.
     */
    template <class O, class = std::enable_if_t<is_ostreamable<O>::value>>
    ANSI_Out &operator<<(O o) {
        os << o;
        return *this;
    }

    using osmanip = std::ostream &(&)(std::ostream &);
    /**
     * Overload used by 'std::endl', 'std::flush', etc...
     * @param osmanip 
     * @return ANSI_Out& 
     */
    ANSI_Out &operator<<(osmanip osmanip);

    /**
     * Custom overload used for colored terminal output (ANSI)
     * @param state New State
     * @return std::ostream& Destination
     */
    ANSI_Out &operator<<(const State &state);
};
} // namespace fpr