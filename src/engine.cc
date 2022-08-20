/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "engine.h"

#include <iostream>

namespace chsmv {

// TODO: Implement ProcessMove
// TODO: Add castling
// TODO: Add deep validation
MoveDescription Engine::IsLegalMove(const Board& board, const Move& move) noexcept {
  if (!board[move.Origin()].has_value()) {
    return MoveDescription::ILLEGAL;
  }
  auto piece = board[move.Origin()].value();

  if (move.Origin() == move.Destination()) {
    return MoveDescription::ILLEGAL;
  }
  if (piece.color != board.MoveTurn()) {
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

Board Engine::ProcessMove(const Board& board, const Move& move) noexcept {
  Board new_board{board};

  // Change move turn
  new_board.MoveTurn() = new_board.MoveTurn() == Piece::Color::WHITE ? Piece::Color::BLACK : Piece::Color::WHITE;

  // Update castling ability
  if (move.Origin().GetIndex() == 0 || move.Destination().GetIndex() == 0) {
    new_board.Castling(Piece::Color::BLACK, Board::CastlingSide::LONG) = false;
  }
  if (move.Origin().GetIndex() == 7 || move.Destination().GetIndex() == 7) {
    new_board.Castling(Piece::Color::BLACK, Board::CastlingSide::SHORT) = false;
  }
  if (move.Origin().GetIndex() == 56 || move.Destination().GetIndex() == 56) {
    new_board.Castling(Piece::Color::WHITE, Board::CastlingSide::LONG) = false;
  }
  if (move.Origin().GetIndex() == 63 || move.Destination().GetIndex() == 63) {
    new_board.Castling(Piece::Color::WHITE, Board::CastlingSide::SHORT) = false;
  }
  if (new_board[move.Origin()]->type == Piece::Type::KING) {
    switch (new_board[move.Origin()]->color) {
      case Piece::Color::WHITE:
        new_board.Castling(Piece::Color::WHITE, Board::CastlingSide::LONG) = false;
        new_board.Castling(Piece::Color::WHITE, Board::CastlingSide::SHORT) = false;
        break;
      case Piece::Color::BLACK:
        new_board.Castling(Piece::Color::BLACK, Board::CastlingSide::LONG) = false;
        new_board.Castling(Piece::Color::BLACK, Board::CastlingSide::SHORT) = false;
        break;
    }
  }

  // Update En passant square
  if (new_board[move.Origin()]->type == Piece::Type::PAWN && IsPawnMove(board, move) && move.RankDistance() == 2) {
    new_board.EnPassantSquare() = Square{move.Origin().GetFile(), move.Origin().GetRank() + move.RankDirection()};
  } else {
    new_board.EnPassantSquare() = std::nullopt;
  }

  // Update halfmove clock
  if (board[move.Origin()]->type == Piece::Type::PAWN || board[move.Destination()].has_value()) {
    new_board.Halfmove() = 0;
  } else {
    new_board.Halfmove()++;
  }

  // Update fullmove counter
  if (board.MoveTurn() == Piece::Color::BLACK) {
    new_board.Fullmove()++;
  }

  // Update board position
  if (new_board[move.Origin()]->type == Piece::Type::KING && IsCastling(board, move)) {
    ProcessCastling(new_board, move);

  } else if (new_board[move.Origin()]->type == Piece::Type::PAWN && IsEnPassant(board, move)) {
    ProcessEnPassant(new_board, move);

  } else if (move.GetPromotion() != Move::Promotion::NONE) {
    ProcessPromotion(new_board, move);

  } else {
    new_board[move.Destination()] = std::nullopt;
    std::swap(new_board[move.Origin()], new_board[move.Destination()]);
  }

  return new_board;
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

void Engine::ProcessCastling(Board& board, const Move& move) noexcept {}

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
  return (move.FileDistance() == 1 && move.RankDistance() == 2) ||
         (move.FileDistance() == 2 && move.RankDistance() == 1);
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

void Engine::ProcessPromotion(Board& board, const Move& move) noexcept {}

bool Engine::IsEnPassant(const Board& board, const Move& move) noexcept {
  if (!IsValidPawnMoveDirection(board, move)) {
    return false;
  }
  return board.EnPassantSquare().has_value() && board.EnPassantSquare().value() == move.Destination() &&
         move.FileDistance() == 1 && move.RankDistance() == 1;
}

void Engine::ProcessEnPassant(Board& board, const Move& move) noexcept {}

}  // namespace chsmv
