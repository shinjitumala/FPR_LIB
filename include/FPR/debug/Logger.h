#pragma once

#include <FPR/out/ansi_out.h>

#include <ostream>

namespace fpr {
class Logger : private ANSI_Out {
  public:
    /** Log levels */
    enum class Level {
        MSG,
        ERR,
        WARN,
        INFO,
    };

    /** Logging level. Any output below this level will be discarded. */
    static Level output_level;
    /** Logging level of this message */
    Level level;
    /** Set to true if outputting */
    const bool is_logged;
    /** Indent level of output */
    static uint indent_level;

    /**
     * @param level Logging level.
     * @param color Output color. Defaults to 'NONE' which sets the color according to 'level'
     */
    Logger(Level level, State::Color color = State::Color::NONE) noexcept;
    /**
     * New line is insterted at destruction.
     */
    ~Logger();

    /**
     * Output operator, but filters out output with insufficient 'level'.
     * @tparam O Streamed type.
     * @tparam std::enable_if_t<is_ansi_streamable<O>::value> Only enabled if 'o' can be streamed from ANSI_Out
     * @param o Streamed value
     * @return Logger& This Logger after the output.
     */
    template <class O, class = std::enable_if_t<is_ansi_streamable<O>::value>>
    Logger &operator<<(O o) {
        if (is_logged) {
            ANSI_Out::operator<<(o);
        }
        return *this;
    }

    Logger &operator<<(osmanip osmanip) {
        if (is_logged) {
            ANSI_Out::operator<<(osmanip);
        }
        return *this;
    }

  protected:
    /**
     * @param level Output level.
     * @return std::ostream& Approproate ostream for 'level'.
     */
    std::ostream &get_ostream(Level level) noexcept;
};
}; // namespace fpr