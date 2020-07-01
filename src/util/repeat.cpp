#include <fpr/util/repeat.h>

namespace fpr {
void
repeat(uint count, function<void()> action)
{
    for (auto i{ 0U }; i < count; i++) {
        action();
    }
}
};