#include <fpr/log/IndentGuard.h>

namespace fpr::log {
IndentGuard::IndentGuard(Indent& indent)
  : indent{ indent }
{
    indent.inc();
}

IndentGuard::~IndentGuard()
{
    indent.dec();
}
};