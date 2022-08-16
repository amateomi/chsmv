/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_MOVE_H_
#define CHSMV_SRC_MOVE_H_

#include <string>
#include <string_view>

#include "square.h"

namespace chsmv {

enum class Promotion { TO_QUEEN, TO_ROOK, TO_BISHOP, TO_KNIGHT, NONE };

struct Move {
  explicit Move(std::string_view move);

  explicit operator std::string() const noexcept;

  Square origin;
  Square destination;
  Promotion promotion;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_MOVE_H_
