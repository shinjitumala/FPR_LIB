#include <FPR/debug/assert.h>

namespace FPR {
inline void asrt(bool &&condition, std::function<void()> failure, std::experimental::source_location loc) {
    if constexpr (debug) {
        if (condition) {
            return;
        }

        failure();
        asm("INT3");
    }
}
} // namespace FPR