#include <fpr/log.h>

namespace fpr::log {
bool
DefaultLogger::should_print()
{
    return true;
};
ostream&
DefaultLogger::get_os()
{
    return cout;
};
void
DefaultLogger::prefix(ostream& os){};
void
DefaultLogger::postfix(ostream& os)
{
    os << "\n";
};
} // namespace fpr::log