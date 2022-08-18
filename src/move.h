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

struct Move {
  // Types
  enum class Promotion { TO_QUEEN, TO_ROOK, TO_BISHOP, TO_KNIGHT, NONE };

  // Constructors
  explicit Move(std::string_view move);

  // Operators
  explicit operator std::string() const noexcept;

  // Functions
  [[nodiscard]] int FileDistance() const noexcept;
  [[nodiscard]] int RankDistance() const noexcept;

  [[nodiscard]] int FileDirection() const noexcept;  //!< Return 1 if move direction is from file a to h, otherwise -1
  [[nodiscard]] int RankDirection() const noexcept;  //!< Return 1 if move direction is from rank 8 to 1, otherwise -1

  // Data
  Square origin;
  Square destination;
  Promotion promotion;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_MOVE_H_
