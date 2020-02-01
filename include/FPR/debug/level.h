#pragma once

#include <FPR/out/ansi_out.h>
#include <ostream>

namespace fpr {
class Logger : public ANSI_Out {
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

    Logger(Level level) noexcept;

    template <class O, class = std::enable_if_t<is_ansi_streamable<O>::value>>
    Logger &operator<<(O o) {
        if (static_cast<uint>(output_level) >= static_cast<uint>(level)) {
            ANSI_Out::operator<<(o);
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