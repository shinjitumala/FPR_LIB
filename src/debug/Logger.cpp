#include <FPR/debug/Logger.h>

namespace fpr {
Logger::Logger(Level level, State::Color color) noexcept
    : ANSI_Out(get_ostream(level)),
      level(level),
      is_logged{static_cast<uint>(output_level) >= static_cast<uint>(level)} {
    if (!is_logged) {
        return;
    }
    State s{
        .bg = State::Color::BLACK,
        .e = State::Emphasis::BOLD,
    };
    if (color != State::Color::NONE) {
        // Change color if 'color' is set
        s.fg = color;
    } else {
        // Use default color for 'level'
        switch (level) {
        case Level::MSG:
            s.fg = State::Color::CYAN;
            break;
        case Level::ERR:
            s.fg = State::Color::RED;
            break;
        case Level::WARN:
            s.fg = State::Color::YELLOW;
            break;
        case Level::INFO:
            s.fg = State::Color::WHITE;
            break;
        }
    }
    *this << s;
    for (int i{0}; i < indent_level; i++) {
        *this << "\t";
    }
}

Logger::~Logger() {
}

Logger::Level Logger::output_level{Level::INFO};
uint Logger::indent_level{0};

std::ostream &Logger::get_ostream(Level level) noexcept {
    switch (level) {
    case Level::MSG:
    case Level::INFO:
        return std::cout;
    case Level::WARN:
    case Level::ERR:
        return std::cout;
    }
}
} // namespace fpr