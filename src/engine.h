/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_ENGINE_H_
#define CHSMV_SRC_ENGINE_H_

#include <chsmv.h>

#include "board.h"
#include "move.h"

namespace chsmv {

class Engine {
 public:
  Engine() = delete;

  static MoveDescription IsPossibleMove(const Board& board, const Move& move) noexcept;

 private:
  static bool IsValidKingMove(const Board& board, const Move& move) noexcept;
  static bool IsValidQueenMove(const Board& board, const Move& move) noexcept;
  static bool IsValidRookMove(const Board& board, const Move& move) noexcept;
  static bool IsValidBishopMove(const Board& board, const Move& move) noexcept;
  static bool IsValidKnightMove(const Board& board, const Move& move) noexcept;
  static bool IsValidPawnMove(const Board& board, const Move& move) noexcept;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_ENGINE_H_
