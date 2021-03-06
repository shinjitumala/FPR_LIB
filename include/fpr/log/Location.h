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
operator<<(ostream& os, const experimental::source_location& loc);
};
};