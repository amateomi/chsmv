/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "chsmv.h"

#include "board.h"
#include "engine.h"
#include "move.h"

namespace chsmv {

MoveDescription ChessMoveAnalyzer::CheckMove(std::string_view board_in_fen, std::string_view move_in_lan) const {
  return Engine::IsLegalMove(Board{board_in_fen}, Move{move_in_lan});
}

std::pair<BoardDescription, std::string> ChessMoveAnalyzer::MakeMove(std::string_view board_in_fen,
                                                                     std::string_view move_in_lan) {
  return {};
}

std::vector<bool> ChessMoveAnalyzer::GetLegalMoves(std::string_view board_in_fen, std::string_view origin) const {
  return {};
}

}  // namespace chsmv
