#include <fpr/debug/assert.h>
#include <fpr/debug/log.h>

namespace fpr {
enum class log::type : uint {
    LAST = type_max,
};
std::vector<bool> log::t{
    []() {
        std::vector<bool> vec;
        vec.resize(static_cast<size_t>(type::LAST) + 1, false);
        vec.at(static_cast<size_t>(type::LAST)) = true;
        return vec;
    }()};

log::lvl log::l{lvl::INF};

u_char log::indent{0};
u_char log::i{std::numeric_limits<u_char>::max()};

log::log(lvl lvl, ansicc cc, std::ostream &out, type type)
    : aout(cc, out) {
    if (lvl == lvl::ERR || lvl == lvl::WRN) {
        print = true;
    } else if (!t[static_cast<size_t>(type)]) {
        print = false;
        return;
    } else if (static_cast<u_char>(lvl) > static_cast<u_char>(l)) {
        print = false;
        return;
    } else if (indent > i) {
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

u_char log::get_indent() {
    return indent;
}

bool log::printed(type type) {
    return t[static_cast<size_t>(type)];
}
} // namespace fpr