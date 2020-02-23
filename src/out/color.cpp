#include <fpr/out/color.h>

namespace fpr {
aout::aout(ansicc cc, std::ostream &out) : os{out} {
    os << cc;
}

aout::~aout() {
    os << ansicc{};
}
} // namespace fpr