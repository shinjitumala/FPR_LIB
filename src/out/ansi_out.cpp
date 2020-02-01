#include <FPR/out/ansi_out.h>
#include <ostream>

namespace fpr {
ANSI_Out::ANSI_Out(std::ostream &os) noexcept : os{os} {}

ANSI_Out &ANSI_Out::operator<<(osmanip o) noexcept {
    os << o;
    return *this;
}

ANSI_Out &ANSI_Out::operator<<(const State &state) noexcept {
    os << "\x1b["; // Escape Character
    bool flag{false};
    if (state.fg != State::Color::NONE) {
        os << static_cast<uint>(state.fg);
        flag = true;
    }
    if (state.bg != State::Color::NONE) {
        if (flag) {
            os << ";";
        }
        os << static_cast<uint>(state.bg) + 10;
        flag = true;
    }
    if (state.e != State::Emphasis::NONE) {
        if (flag) {
            os << ";";
        }
        os << static_cast<uint>(state.e);
    }
    os << "m"; // End
    return *this;
}

ANSI_Out::~ANSI_Out() {
    *this << reset();
}
} // namespace fpr