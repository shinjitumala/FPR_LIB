#include <FPR/out/ansi_out.h>
#include <ostream>

namespace FPR {
std::ostream &operator<<(std::ostream &os, const ANSI_State &state) {
    os << "\033["; // Escape Character
    if (state.fg != ANSI_State::Color::NONE) {
        os << static_cast<uint>(state.fg);
    }
    os << ";";
    if (state.bg != ANSI_State::Color::NONE) {
        os << static_cast<uint>(state.bg) + 10;
    }
    os << ";";
    if (state.e != ANSI_State::Emphasis::NONE) {
        os << static_cast<uint>(state.e);
    }
    os << "m"; // End
    return os;
}
} // namespace FPR