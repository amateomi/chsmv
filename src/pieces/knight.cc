#include "knight.h"

namespace chsmv {

Conditions Knight::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions Knight::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
