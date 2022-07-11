#include "pawn.h"

namespace chsmv {

Conditions Pawn::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions Pawn::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
