#include "king.h"

namespace chsmv {

Conditions King::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions King::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
