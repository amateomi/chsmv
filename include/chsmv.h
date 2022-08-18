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

enum class MoveDescription { LEGAL, ILLEGAL, PAWN_PROMOTION_NOT_SPECIFIED };
enum class BoardDescription { NOTHING_SPECIAL, CHECK, CHECKMATE, DRAW };

class ChessMoveAnalyzer {
 public:
  [[nodiscard]] MoveDescription CheckMove(std::string_view board_in_fen, std::string_view move_in_lan) const;

  [[nodiscard]] std::pair<BoardDescription, std::string> MakeMove(std::string_view board_in_fen,
                                                                  std::string_view move_in_lan);

  [[nodiscard]] std::vector<bool> GetLegalMoves(std::string_view board_in_fen, std::string_view origin) const;

 private:
  std::list<std::string> move_history_;
};

}  // namespace chsmv

#endif  // CHSMV_INCLUDE_CHSMV_H_
