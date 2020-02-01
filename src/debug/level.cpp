#include <FPR/debug/level.h>

namespace fpr {
Logger::Logger(Level level) noexcept : ANSI_Out(get_ostream(level)), level(level) {
}

Logger::Level Logger::output_level{Level::INFO};

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