#include <FPR/out/ansicc.h>

fpr::ansicc::ansicc()
    : bg{Color::NONE},
      fg{Color::NONE},
      e{Emphasis::RESET} {}

fpr::ansicc::ansicc(Color bg, Color fg, Emphasis e)
    : bg{bg},
      fg{fg},
      e{e} {}

std::ostream &operator<<(std::ostream &os, fpr::ansicc cc) {
    os << "\x1b["; // Escape Character
    bool flag{false};
    if (cc.fg != fpr::ansicc::Color::NONE) {
        os << static_cast<uint>(cc.fg);
        flag = true;
    }
    if (cc.bg != fpr::ansicc::Color::NONE) {
        if (flag) {
            os << ";";
        }
        os << static_cast<uint>(cc.bg) + 10;
        flag = true;
    }
    if (cc.e != fpr::ansicc::Emphasis::NONE) {
        if (flag) {
            os << ";";
        }
        os << static_cast<uint>(cc.e);
    }
    os << "m"; // End
    return os;
}
