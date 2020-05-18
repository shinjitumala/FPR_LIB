#pragma once

#include <experimental/source_location>
#include <ostream>

namespace fpr {
using namespace std;
namespace log {
/// Use this to print a source location.
/// @param os
/// @param loc
/// @return ostream&
ostream&
operator<<(ostream& os, experimental::source_location& loc)
{
    os << loc.file_name() << ":" << loc.line() << ":" << loc.column() << " "
       << loc.function_name();
    return os;
}
};
};