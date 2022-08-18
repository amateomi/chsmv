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
    auto file{'a'};
    auto rank{'8'};
    for (auto item : pieces) {
      if (file > 'h' && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        --rank;
        file = 'a';
      } else if (std::isdigit(item)) {
        file = static_cast<char>(file + (item - '0'));
      } else {
        this->squares[Square::ToIndex(file, rank)] = Piece::Factory(item);
        ++file;
      }
    }

    std::string turn;
    iss >> turn;
    this->move_turn = turn == "w" ? Piece::Color::WHITE : Piece::Color::BLACK;

    std::string castling;
    iss >> castling;
    for (auto i{0}; i < this->castling_ability.size(); ++i) {
      this->castling_ability[i] = castling.find(castling_chars_in_fen[i]) != std::string::npos;
    }

    std::string en_passant;
    iss >> en_passant;
    this->en_passant_square = en_passant == "-" ? std::nullopt : std::make_optional<Square>(en_passant);

    iss >> this->halfmove_count >> this->fullmove_count;
    if (this->halfmove_count > 50) {
      throw std::exception{};
    }
  } catch (const std::exception&) {
    throw std::domain_error('\"' + std::string{board_in_fen} + '\"' +
                            " is invalid FEN board\n"
                            "Right FEN: <FEN> = <Piece Placement> <Side to move> <Castling ability> <En passant target "
                            "square> <Halfmove clock> <Fullmove counter>\n"
                            "Example: " +
                            start_board_position_in_fen);
  }
}

Board::operator std::string() const noexcept {
  std::ostringstream oss;

  for (auto i{0}; i < squares.size(); ++i) {
    if (i % 8 == 0 && i != 0) {
      oss << '/';
    }
    if (squares[i].has_value()) {
      oss << static_cast<char>(squares[i].value());
    } else {
      auto empty_squares_count{1};
      while (i % 8 != 7) {
        if (squares[i + 1].has_value()) {
          break;
        }
        ++empty_squares_count;
        ++i;
      }
      oss << empty_squares_count;
    }
  }

  oss << ' ' << (move_turn == Piece::Color::WHITE ? 'w' : 'b') << ' ';

  if (std::find(castling_ability.begin(), castling_ability.end(), true) == castling_ability.end()) {
    oss << '-';
  } else {
    for (auto i{0}; i < this->castling_ability.size(); ++i) {
      if (castling_ability[i]) {
        oss << castling_chars_in_fen[i];
      }
    }
  }

  oss << ' ' << (en_passant_square.has_value() ? static_cast<std::string>(en_passant_square.value()) : "-");

  oss << ' ' << halfmove_count << ' ' << fullmove_count;

  return oss.str();
}

Board::OptionalPiece& Board::operator[](int index) noexcept {
  assert(0 <= index && index < squares.size());
  return squares[index];
}
const Board::OptionalPiece& Board::operator[](int index) const noexcept {
  assert(0 <= index && index < squares.size());
  return squares[index];
}
Board::OptionalPiece& Board::operator[](const Square& square) noexcept { return squares[square.index]; }
const Board::OptionalPiece& Board::operator[](const Square& square) const noexcept { return squares[square.index]; }

bool& Board::GetCastling(Piece::Color color, Board::CastlingSide side) noexcept {
  return castling_ability[(color == Piece::Color::WHITE ? 0 : 2) + (side == CastlingSide::KING ? 0 : 1)];
}
const bool& Board::GetCastling(Piece::Color color, Board::CastlingSide side) const noexcept {
  return castling_ability[(color == Piece::Color::WHITE ? 0 : 2) + (side == CastlingSide::KING ? 0 : 1)];
}

}  // namespace chsmv
