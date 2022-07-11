/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "bishop.h"

namespace chsmv {

Conditions Bishop::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions Bishop::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
