/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "king.h"

namespace chsmv {

Conditions King::GetMoveConditions(const Move& move) const noexcept { return chsmv::Conditions(); }
Conditions King::GetCaptureConditions(const Move& move) const noexcept { return chsmv::Conditions(); }

}  // namespace chsmv
