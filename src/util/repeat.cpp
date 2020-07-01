#include <fpr/util/repeat.h>

namespace fpr {
void
repeat(uint count, function<void()> action)
{
    for (auto i{ 0 }; i < count; i++) {
        action();
    }
}
};