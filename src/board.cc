/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "board.h"

#include <cassert>
#include <numeric>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace chsmv {

Board::Board(std::string_view board_in_fen) {
  try {
    std::regex re{"([kqrbnpKQRBNP1-8]{1,8}/){7}[kqrbnpKQRBNP1-8]{1,8} [wb] (-|(K?Q?k?q?)) (-|[a-h][36])( [0-9]*){2}"};
    if (!std::regex_match(std::string{board_in_fen}, re)) {
      throw std::exception{};
    }
    std::istringstream iss{board_in_fen.data()};

    std::string pieces;
    iss >> pieces;
    Square square;
    auto file{0};
    auto rank{0};
    for (auto item : pieces) {
      if (file >= Square::total_files_ && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        ++rank;
        file = 0;
      } else if (std::isdigit(item)) {
        file += item - '0';
      } else {
        (*this)[Square{file, rank}] = Piece::Factory(item);
        ++file;
      }
    }

    std::string turn;
    iss >> turn;
    move_turn_ = turn == "w" ? Piece::Color::WHITE : Piece::Color::BLACK;

    std::string castling;
    iss >> castling;
    for (auto i{0}; i < castling_ability_.size(); ++i) {
      castling_ability_[i] = castling.find(castling_chars_in_fen_[i]) != std::string::npos;
    }

    std::string en_passant;
    iss >> en_passant;
    en_passant_square_ = en_passant == "-" ? std::nullopt : std::make_optional<Square>(en_passant);

    iss >> halfmove_count_ >> fullmove_count_;
    if (halfmove_count_ > 50) {
      throw std::exception{};
    }
  } catch (const std::exception&) {
    throw std::domain_error('\"' + std::string{board_in_fen} + '\"' +
                            " is invalid FEN board\n"
                            "Right FEN: <FEN> = <Piece Placement> <Side to move> <Castling ability> <En passant target "
                            "square> <Halfmove clock> <Fullmove counter>\n"
                            "Example: " +
                            start_board_position_in_fen_);
  }
}

Board::operator std::string() const noexcept {
  std::ostringstream oss;

  for (auto i{0}; i < squares_.size(); ++i) {
    if (i % Square::total_files_ == 0 && i != 0) {
      oss << '/';
    }
    if (squares_[i].has_value()) {
      oss << static_cast<char>(squares_[i].value());
    } else {
      auto empty_squares_count{1};
      while (i % 8 != 7) {
        if (squares_[i + 1].has_value()) {
          break;
        }
        ++empty_squares_count;
        ++i;
      }
      oss << empty_squares_count;
    }
  }

  oss << ' ' << (move_turn_ == Piece::Color::WHITE ? 'w' : 'b') << ' ';

  if (std::find(castling_ability_.begin(), castling_ability_.end(), true) == castling_ability_.end()) {
    oss << '-';
  } else {
    for (auto i{0}; i < castling_ability_.size(); ++i) {
      if (castling_ability_[i]) {
        oss << castling_chars_in_fen_[i];
      }
    }
  }

  oss << ' ' << (en_passant_square_.has_value() ? static_cast<std::string>(en_passant_square_.value()) : "-");

  oss << ' ' << halfmove_count_ << ' ' << fullmove_count_;

  return oss.str();
}

Board::OptionalPiece& Board::operator[](int index) noexcept {
  assert(0 <= index && index < squares_.size());
  return squares_[index];
}
const Board::OptionalPiece& Board::operator[](int index) const noexcept {
  assert(0 <= index && index < squares_.size());
  return squares_[index];
}
Board::OptionalPiece& Board::operator[](const Square& square) noexcept { return squares_[square.GetIndex()]; }
const Board::OptionalPiece& Board::operator[](const Square& square) const noexcept {
  return squares_[square.GetIndex()];
}

Piece::Color& Board::MoveTurn() noexcept { return move_turn_; }
Piece::Color Board::MoveTurn() const noexcept { return move_turn_; }

bool& Board::Castling(Piece::Color color, Board::CastlingSide side) noexcept {
  return castling_ability_[(color == Piece::Color::WHITE ? 0 : 2) + (side == CastlingSide::SHORT ? 0 : 1)];
}
bool Board::Castling(Piece::Color color, Board::CastlingSide side) const noexcept {
  return castling_ability_[(color == Piece::Color::WHITE ? 0 : 2) + (side == CastlingSide::SHORT ? 0 : 1)];
}

std::optional<Square>& Board::EnPassantSquare() noexcept { return en_passant_square_; }
const std::optional<Square>& Board::EnPassantSquare() const noexcept { return en_passant_square_; }

int& Board::Halfmove() noexcept { return halfmove_count_; }
int Board::Halfmove() const noexcept { return halfmove_count_; }

int& Board::Fullmove() noexcept { return fullmove_count_; }
int Board::Fullmove() const noexcept { return fullmove_count_; }

}  // namespace chsmv
