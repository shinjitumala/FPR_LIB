#include <fpr/debug/assert.h>
#include <fpr/debug/log.h>

namespace fpr {
enum class log::type : u_char {
    LAST = lvl_max,
};
std::vector<bool> log::t{
    []() {
        std::vector<bool> vec;
        vec.resize(static_cast<size_t>(type::LAST), true);
        return vec;
    }()};

log::lvl log::l{lvl::INF};

u_char log::indent{0};
u_char log::i{std::numeric_limits<u_char>::max()};

log::log(lvl lvl, ansicc cc, std::ostream &out, type type)
    : aout(cc, out) {
    if (!t[static_cast<u_char>(type)]) {
        print = false;
        return;
    }
    if (static_cast<u_char>(lvl) > static_cast<u_char>(l)) {
        print = false;
        return;
    }
    if (indent > i) {
        print = false;
        return;
    }

    print = true;
    for (ushort i{0U}; i < indent; i++) {
        os << "\t";
    }
}

void log::ii() {
    indent++;
}

void log::di() {
    asrt(indent > 0U, std::cout << "Negative Indent!");
    indent--;
}
} // namespace fpr