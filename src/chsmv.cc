/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "chsmv.h"

namespace chsmv {

MoveStatus ChessMoveAnalyzer::CheckMove(const BoardString& board, const MoveString& move) const {
  return MoveStatus::VALID;
}

BoardString ChessMoveAnalyzer::MakeMove(const BoardString& board, const MoveString& move, History option) {
  return std::string();
}

BoardState ChessMoveAnalyzer::GetBoardState(const BoardString& board) { return BoardState::WHITE_WIN; }

AvailableMoves ChessMoveAnalyzer::GetAvailableMoves(const BoardString& board, const SquareString& square,
                                                    Cache option) {
  return chsmv::AvailableMoves();
}

}  // namespace chsmv
