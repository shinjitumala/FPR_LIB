#pragma once

#include <fpr/log/callback/Indent.h>

namespace fpr::log {
/// Indent utility.
class IndentGuard
{
    /// The indent we are guarding.
    Indent& indent;

  public:
    /// Increases indent.
    /// @param indent
    IndentGuard(Indent& indent);
    /// Decreases Indent.
    ~IndentGuard();

  private:
    /// No copies allowed.
    IndentGuard(const IndentGuard&) = delete;
};
};