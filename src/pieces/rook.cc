#include "rook.h"

namespace chsmv {

Conditions Rook::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions Rook::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
