#include "bishop.h"

namespace chsmv {

Conditions Bishop::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions Bishop::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
