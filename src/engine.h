/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_ENGINE_H_
#define CHSMV_SRC_ENGINE_H_

#include <chsmv.h>

#include <vector>

#include "board.h"
#include "move.h"
#include "piece.h"
#include "square.h"

namespace chsmv {

class Engine {
 public:
  // Constructors
  Engine() = delete;

  // Functions
  static MoveDescription IsLegalMove(const Board& board, const Move& move) noexcept;
  static std::pair<BoardDescription, std::string> ProcessMove(const Board& board, const Move& move) noexcept;
  static std::vector<bool> GetAllLegalMoves(const Board& board, const Square& origin) noexcept;

 private:
  static bool IsSameColor(Piece first, Board::OptionalPiece second) noexcept;

  static bool IsKingMove(const Board& board, const Move& move) noexcept;
  static bool IsCastling(const Board& board, const Move& move) noexcept;

  static bool IsQueenMove(const Board& board, const Move& move) noexcept;
  static bool IsRookMove(const Board& board, const Move& move) noexcept;
  static bool IsBishopMove(const Board& board, const Move& move) noexcept;
  static bool IsKnightMove(const Board& board, const Move& move) noexcept;

  static bool IsPawnMove(const Board& board, const Move& move) noexcept;
  static bool IsValidPawnMoveDirection(const Board& board, const Move& move) noexcept;
  static bool IsPawnPromotion(const Board& board, const Move& move) noexcept;
  static bool IsEnPassant(const Board& board, const Move& move) noexcept;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_ENGINE_H_
