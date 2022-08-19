/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "engine.h"

#include <cstdlib>
#include <iostream>

namespace chsmv {

// TODO: Add deep validation
// TODO: Add more variants for MoveDescription
MoveDescription Engine::IsLegalMove(const Board& board, const Move& move) noexcept {
  if (!board[move.Origin()].has_value()) {
    return MoveDescription::ILLEGAL;
  }
  auto piece = board[move.Origin()].value();

  if (move.Origin() == move.Destination()) {
    return MoveDescription::ILLEGAL;
  }
  if (piece.color != board.GetMoveTurn()) {
    return MoveDescription::ILLEGAL;
  }
  if (IsSameColor(piece, board[move.Destination()])) {
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
      if (IsPawnPromotion(board, move) && move.GetPromotion() == Move::Promotion::NONE) {
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
  std::vector<bool> legal_moves(Square::total_squares_);

  Move move{static_cast<std::string>(origin) + "a8"};
  auto& square = move.Destination();
  for (auto i{0}; i < Square::total_squares_; ++i) {
    legal_moves[i] = IsLegalMove(board, move) != MoveDescription::ILLEGAL;
    if (i % 8 == 0) {
      std::cout << '\n';
    }
    std::cout << legal_moves[i] << ' ';
    ++square;
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

bool Engine::IsCastling(const Board& board, const Move& move) noexcept { return false; }

bool Engine::IsQueenMove(const Board& board, const Move& move) noexcept {
  return IsRookMove(board, move) || IsBishopMove(board, move);
}

bool Engine::IsRookMove(const Board& board, const Move& move) noexcept {
  Square square{move.Origin()};

  if (move.Origin().GetFile() == move.Destination().GetFile()) {
    auto step{move.RankDirection()};

    square.SetRank(square.GetRank() + step);
    while (square != move.Destination()) {
      if (board[square].has_value()) {
        return false;
      }
      square.SetRank(square.GetRank() + step);
    }
    return true;

  } else if (move.Origin().GetRank() == move.Destination().GetRank()) {
    auto step{move.FileDirection()};

    square.SetFile(square.GetFile() + step);
    while (square != move.Destination()) {
      if (board[square].has_value()) {
        return false;
      }
      square.SetFile(square.GetFile() + step);
    }
    return true;
  }
  return false;
}

bool Engine::IsBishopMove(const Board& board, const Move& move) noexcept {
  if (move.FileDistance() != move.RankDistance()) {
    return false;
  }
  Square square{move.Origin()};

  auto file_step{move.FileDirection()};
  auto rank_step{move.RankDirection()};

  square.SetFile(square.GetFile() + file_step);
  square.SetRank(square.GetRank() + rank_step);
  while (square != move.Destination()) {
    if (board[square].has_value()) {
      return false;
    }
    square.SetFile(square.GetFile() + file_step);
    square.SetRank(square.GetRank() + rank_step);
  }
  return true;
}

bool Engine::IsKnightMove(const Board& board, const Move& move) noexcept {
  if (board[move.Destination()].has_value() && board[move.Destination()]->color == board[move.Origin()]->color) {
    return false;
  }
  return abs(move.FileDistance() - move.RankDistance()) == 1;
}

bool Engine::IsPawnMove(const Board& board, const Move& move) noexcept {
  if (!IsValidPawnMoveDirection(board, move)) {
    return false;
  }
  if (board[move.Destination()].has_value()) {
    return move.FileDistance() == 1 && move.RankDistance() == 1;
  }
  switch (move.RankDistance()) {
    case 2: {
      Square middle_square{move.Origin().GetFile(), move.Origin().GetRank() + move.RankDirection()};
      return move.FileDistance() == 0 && !board[middle_square].has_value() &&
             (move.Origin().GetRank() == 1 || move.Origin().GetRank() == Square::total_ranks_ - 2);
    }
    case 1:
      return move.FileDistance() == 0;
    default:
      return false;
  }
}

bool Engine::IsValidPawnMoveDirection(const Board& board, const Move& move) noexcept {
  return board[move.Origin()]->color == Piece::Color::WHITE && move.RankDirection() == -1 ||
         board[move.Origin()]->color == Piece::Color::BLACK && move.RankDirection() == 1;
}

bool Engine::IsPawnPromotion(const Board& board, const Move& move) noexcept {
  return IsPawnMove(board, move) &&
         (move.Destination().GetRank() == 0 || move.Destination().GetRank() == Square::total_ranks_ - 1);
}

bool Engine::IsEnPassant(const Board& board, const Move& move) noexcept {
  if (!IsValidPawnMoveDirection(board, move)) {
    return false;
  }
  return board.GetEnPassantSquare().has_value() && board.GetEnPassantSquare().value() == move.Destination() &&
         move.FileDistance() == 1 && move.RankDistance() == 1;
}

}  // namespace chsmv
