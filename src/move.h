/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_MOVE_H_
#define CHSMV_SRC_MOVE_H_

#include <string>

#include "square.h"

namespace chsmv {

enum class Promotion { TO_QUEEN, TO_ROOK, TO_BISHOP, TO_KNIGHT, NONE };

class Move {
 public:
  explicit Move(const std::string& move);

  explicit operator std::string() const noexcept;

  [[nodiscard]] const Square& GetOrigin() const noexcept;
  [[nodiscard]] const Square& GetDestination() const noexcept;
  [[nodiscard]] const Promotion& GetPromotion() const noexcept;

 private:
  Square origin_;
  Square destination_;
  Promotion promotion_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_MOVE_H_
