#include <FPR/out/ansi_out.h>
#include <ostream>

namespace fpr {
ANSI_Out::ANSI_Out(std::ostream &os) : os{os} {}

ANSI_Out &ANSI_Out::operator<<(osmanip o) {
    os << o;
    return *this;
}

ANSI_Out &ANSI_Out::operator<<(const State &state) {
    os << "\033["; // Escape Character
    if (state.fg != State::Color::NONE) {
        os << static_cast<uint>(state.fg);
    }
    os << ";";
    if (state.bg != State::Color::NONE) {
        os << static_cast<uint>(state.bg) + 10;
    }
    os << ";";
    if (state.e != State::Emphasis::NONE) {
        os << static_cast<uint>(state.e);
    }
    os << "m"; // End
    return *this;
}
} // namespace fpr