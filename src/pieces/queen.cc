#include "queen.h"

namespace chsmv {

Conditions Queen::GetMoveConditions(const Move& move) const noexcept { return Rook::GetMoveConditions(move); }
Conditions Queen::GetCaptureConditions(const Move& move) const noexcept { return Rook::GetCaptureConditions(move); }

}  // namespace chsmv
