/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "engine.h"

#include <cstdlib>

namespace chsmv {

MoveDescription Engine::IsPossibleMove(const Board& board, const Move& move) noexcept {
  if (!board[move.origin].has_value()) {
    return MoveDescription::IMPOSSIBLE_MOVE;
  }
  auto piece = board[move.origin].value();
  if (piece.color != board.move_turn) {
    return MoveDescription::IMPOSSIBLE_MOVE;
  }

  auto is_move_success = false;
  switch (piece.type) {
    case Piece::Type::KING:
      is_move_success = Engine::IsValidKingMove(board, move);
      break;
    case Piece::Type::QUEEN:
      is_move_success = Engine::IsValidQueenMove(board, move);
      break;
    case Piece::Type::ROOK:
      is_move_success = Engine::IsValidRookMove(board, move);
      break;
    case Piece::Type::BISHOP:
      is_move_success = Engine::IsValidBishopMove(board, move);
      break;
    case Piece::Type::KNIGHT:
      is_move_success = Engine::IsValidKnightMove(board, move);
      break;
    case Piece::Type::PAWN:
      is_move_success = Engine::IsValidPawnMove(board, move);
      break;
  }

  return is_move_success ? MoveDescription::POSSIBLE_MOVE : MoveDescription::IMPOSSIBLE_MOVE;
}

bool Engine::IsValidKingMove(const Board& board, const Move& move) noexcept {
  auto file_delta = move.origin.file - move.destination.file;
  auto rank_delta = move.origin.rank - move.destination.rank;
  return abs(file_delta) == 1 && abs(rank_delta) == 1;
}

bool Engine::IsValidQueenMove(const Board& board, const Move& move) noexcept {
  return IsValidRookMove(board, move) || IsValidBishopMove(board, move);
}

bool Engine::IsValidRookMove(const Board& board, const Move& move) noexcept {
  if (move.origin.file == move.destination.file) {
    auto file = move.origin.file;
    auto direction = move.FileDirection();
    for (auto rank{move.origin.rank + 1}; rank != move.destination.rank; rank += direction) {
      if (board[Square{file, rank}].has_value()) {
        return false;
      }
    }
    return true;

  } else if (move.origin.rank == move.destination.rank) {
    auto rank = move.origin.rank;
    auto direction = move.RankDirection();
    for (auto file{move.origin.file + 1}; file != move.destination.file; file += direction) {
      if (board[Square{file, rank}].has_value()) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool Engine::IsValidBishopMove(const Board& board, const Move& move) noexcept {
  if (abs(move.destination.file - move.origin.file) != abs(move.destination.rank - move.origin.rank)) {
    return false;
  }
  auto file_direction = move.FileDirection();
  auto rank_direction = move.RankDirection();
  for (auto file{move.origin.file}, rank{move.origin.rank}; Square{file, rank} != move.destination;
       file += rank_direction, rank += file_direction) {
    if (board[Square{file, rank}].has_value()) {
      return false;
    }
  }
  return true;
}

bool Engine::IsValidKnightMove(const Board& board, const Move& move) noexcept { return false; }

bool Engine::IsValidPawnMove(const Board& board, const Move& move) noexcept { return false; }

}  // namespace chsmv
