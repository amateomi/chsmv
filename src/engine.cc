/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "engine.h"

#include <cstdlib>

namespace chsmv {

// TODO: Add deep validation
// TODO: Add more variants for MoveDescription
MoveDescription Engine::IsLegalMove(const Board& board, const Move& move) noexcept {
  if (!board[move.origin].has_value()) {
    return MoveDescription::ILLEGAL;
  }
  auto piece = board[move.origin].value();

  if (move.origin == move.destination) {
    return MoveDescription::ILLEGAL;
  }
  if (piece.color != board.move_turn) {
    return MoveDescription::ILLEGAL;
  }
  if (IsSameColor(piece, board[move.destination])) {
    return MoveDescription::ILLEGAL;
  }
  auto is_move_success{false};
  switch (piece.type) {
    case Piece::Type::KING:
      is_move_success = IsKingMove(board, move) || IsCastling(board, move);
      break;
    case Piece::Type::QUEEN:
      is_move_success = IsQueenMove(board, move);
      break;
    case Piece::Type::ROOK:
      is_move_success = IsRookMove(board, move);
      break;
    case Piece::Type::BISHOP:
      is_move_success = IsBishopMove(board, move);
      break;
    case Piece::Type::KNIGHT:
      is_move_success = IsKnightMove(board, move);
      break;
    case Piece::Type::PAWN:
      if (IsPawnPromotion(board, move) && move.promotion == Move::Promotion::NONE) {
        return MoveDescription::PAWN_PROMOTION_NOT_SPECIFIED;
      }
      is_move_success = IsPawnMove(board, move) || IsEnPassant(board, move);
      break;
  }

  return is_move_success ? MoveDescription::LEGAL : MoveDescription::ILLEGAL;
}

std::pair<BoardDescription, std::string> Engine::ProcessMove(const Board& board, const Move& move) noexcept {
  return {};
}

std::vector<bool> Engine::GetAllLegalMoves(const Board& board, const Square& origin) noexcept {
  std::vector<bool> legal_moves(Board::size);
  for (auto rank{'8'}; rank >= '1'; --rank) {
    for (auto file{'a'}; file <= 'h'; ++file) {
      Move move{static_cast<std::string>(origin) + file + rank};
      legal_moves[Square::ToIndex(file, rank)] = IsLegalMove(board, move) != MoveDescription::ILLEGAL;
    }
  }
  return legal_moves;
}

bool Engine::IsSameColor(Piece first, Board::OptionalPiece second) noexcept {
  return second.has_value() && first.color == second->color;
}

bool Engine::IsKingMove(const Board& board, const Move& move) noexcept {
  return (move.FileDistance() == 0 || move.FileDistance() == 1) &&
         (move.RankDistance() == 0 || move.RankDistance() == 1);
}

bool Engine::IsCastling(const Board& board, const Move& move) noexcept {
  return false;
}

bool Engine::IsQueenMove(const Board& board, const Move& move) noexcept {
  return IsRookMove(board, move) || IsBishopMove(board, move);
}

bool Engine::IsRookMove(const Board& board, const Move& move) noexcept {
  if (move.origin.file == move.destination.file) {
    auto file{move.origin.file};
    auto direction{move.RankDirection()};
    for (auto rank{move.origin.rank + 1}; rank != move.destination.rank; rank += direction) {
      if (board[Square::ToIndex(file, rank)].has_value()) {
        return false;
      }
    }
    return true;

  } else if (move.origin.rank == move.destination.rank) {
    auto rank{move.origin.rank};
    auto direction{move.FileDirection()};
    for (auto file{move.origin.file + 1}; file != move.destination.file; file += direction) {
      if (board[Square::ToIndex(file, rank)].has_value()) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool Engine::IsBishopMove(const Board& board, const Move& move) noexcept {
  if (move.FileDistance() != move.RankDistance()) {
    return false;
  }
  auto file_direction{move.RankDirection()};
  auto rank_direction{move.FileDirection()};
  for (auto file{move.origin.file}, rank{move.origin.rank};
       file != move.destination.file && rank != move.destination.rank; file += rank_direction, rank += file_direction) {
    if (board[Square::ToIndex(file, rank)].has_value()) {
      return false;
    }
  }
  return true;
}

bool Engine::IsKnightMove(const Board& board, const Move& move) noexcept {
  if (board[move.destination].has_value() && board[move.destination]->color == board[move.origin]->color) {
    return false;
  }
  return abs(move.FileDistance() - move.RankDistance()) == 1;
}

bool Engine::IsPawnMove(const Board& board, const Move& move) noexcept {
  if (!IsValidPawnMoveDirection(board, move)) {
    return false;
  }
  if (board[move.destination].has_value()) {
    return move.FileDistance() == 1 && move.RankDistance() == 1;
  }
  switch (move.RankDistance()) {
    case 2:
      return move.FileDistance() == 0 && (move.origin.rank == 1 || move.origin.rank == 6);
    case 1:
      return move.FileDistance() == 0;
    default:
      return false;
  }
}

bool Engine::IsValidPawnMoveDirection(const Board& board, const Move& move) noexcept {
  return board[move.origin]->color == Piece::Color::WHITE && move.RankDirection() != -1 ||
         board[move.origin]->color == Piece::Color::BLACK && move.RankDirection() != 1;
}

bool Engine::IsPawnPromotion(const Board& board, const Move& move) noexcept {
  return IsPawnMove(board, move) && (move.destination.rank == 0 || move.destination.rank == 7);
}

bool Engine::IsEnPassant(const Board& board, const Move& move) noexcept {
  if (!IsValidPawnMoveDirection(board, move)) {
    return false;
  }
  return board.en_passant_square.has_value() && board.en_passant_square.value() == move.destination &&
         move.FileDistance() == 1 && move.RankDistance() == 1;
}

}  // namespace chsmv
