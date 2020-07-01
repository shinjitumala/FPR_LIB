#include <fpr/log/Location.h>

namespace fpr{
ostream&
operator<<(ostream& os, const experimental::source_location& loc)
{
    os << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " "
       << loc.function_name();
    return os;
}
};