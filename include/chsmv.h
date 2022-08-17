/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_INCLUDE_CHSMV_H_
#define CHSMV_INCLUDE_CHSMV_H_

#include <list>
#include <string>
#include <string_view>
#include <vector>

namespace chsmv {

enum class MoveDescription { POSSIBLE_MOVE, IMPOSSIBLE_MOVE, PAWN_PROMOTION_NOT_SPECIFIED };

class ChessMoveAnalyzer {
 public:
  [[nodiscard]] MoveDescription CheckMove(std::string_view board_in_fen, std::string_view move_in_lan) const;

  [[nodiscard]] std::string MakeMove(std::string_view board_in_fen, std::string_view move_in_lan);

  [[nodiscard]] std::vector<bool> GetAvailableMoves(std::string_view board_in_fen, std::string_view square) const;

 private:
  std::list<std::string> move_history_;
};

}  // namespace chsmv

#endif  // CHSMV_INCLUDE_CHSMV_H_
