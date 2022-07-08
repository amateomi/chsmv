/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_INCLUDE_CHSMV_H_
#define CHSMV_INCLUDE_CHSMV_H_

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace chsmv {

enum class History { ENABLE, DISABLE };
enum class Cache { ENABLE, DISABLE };
enum class MoveStatus { VALID, INVALID, MISSING_PAWN_PROMOTION };
enum class BoardState { OK, DRAW, BLACK_WIN, WHITE_WIN };

using BoardString = std::string;
using MoveString = std::string;
using SquareString = std::string;
using AvailableMoves = std::vector<bool>;

class ChessMoveAnalyzer {
 public:
  ChessMoveAnalyzer() = default;

  [[nodiscard]] MoveStatus CheckMove(const BoardString& board, const MoveString& move) const;

  BoardString MakeMove(const BoardString& board, const MoveString& move, History option);

  BoardState GetBoardState(const BoardString& board);

  AvailableMoves GetAvailableMoves(const BoardString& board, const SquareString& square, Cache option);

  private:
  std::optional<std::vector<MoveString>> move_history_{std::in_place};
  std::optional<std::map<BoardString, AvailableMoves>> board_moves_cache_{std::in_place};
};

}  // namespace chsmv

#endif  // CHSMV_INCLUDE_CHSMV_H_
