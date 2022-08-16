/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "chsmv.h"

#include "board.h"

namespace chsmv {

MoveStatus ChessMoveAnalyzer::CheckMove(std::string_view board_in_fen, std::string_view move_in_lan) const {
  Board board{board_in_fen};
}

std::string ChessMoveAnalyzer::MakeMove(std::string_view board_in_fen, std::string_view move_in_lan) const {
  return std::string();
}

std::vector<bool> ChessMoveAnalyzer::GetAvailableMoves(std::string_view board_in_fen, std::string_view square) const {
  return std::vector<bool>();
}

}  // namespace chsmv
