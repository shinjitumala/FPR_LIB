#include <experimental/source_location>
#include <functional>

namespace FPR {
#ifdef DEBUG
const bool debug{true};
#else
const bool debug{false};
#endif

/**
 * Assert that does not use the pre processor.
 * @param condition Program will crash if this is not true.
 * @param failure Actions to take before crashing. Defaults to 'Do nothing'.
 * @param loc Source location to be displayed if the assertion fails.
 */
inline void asrt(
    bool &&condition,
    std::function<void()> failure = []() {},
    std::experimental::source_location loc = std::experimental::source_location::current());

} // namespace FPR