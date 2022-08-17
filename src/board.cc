/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "board.h"

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

    std::string squares;
    iss >> squares;
    auto file{'a'};
    auto rank{'8'};
    for (auto item : squares) {
      if (file > 'h' && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        --rank;
        file = 'a';
      } else if (std::isdigit(item)) {
        file = static_cast<char>(file + (item - '0'));
      } else {
        this->operator[](Square{file, rank}) = Piece::Factory(item);
        ++file;
      }
    }

    std::string turn;
    iss >> turn;
    this->move_turn = turn == "w" ? Piece::Color::WHITE : Piece::Color::BLACK;

    std::string castling;
    iss >> castling;
    auto set_castling = [this, &castling](Piece::Color color, CastlingSide side, char piece) {
      this->operator[](std::pair{color, side}) = castling.find(piece) != std::string::npos;
    };
    set_castling(Piece::Color::WHITE, CastlingSide::KING, 'K');
    set_castling(Piece::Color::WHITE, CastlingSide::QUEEN, 'Q');
    set_castling(Piece::Color::BLACK, CastlingSide::KING, 'k');
    set_castling(Piece::Color::BLACK, CastlingSide::QUEEN, 'q');

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

  for (auto i{0}; i < size; ++i) {
    if (i % 8 == 0 && i != 0) {
      oss << '/';
    }
    if (board[i].has_value()) {
      oss << static_cast<char>(board[i].value());
    } else {
      auto empty_squares_count{1};
      while (i % 8 != 7) {
        if (board[i + 1].has_value()) {
          break;
        }
        ++empty_squares_count;
        ++i;
      }
      oss << empty_squares_count;
    }
  }

  oss << ' ' << (move_turn == Piece::Color::WHITE ? 'w' : 'b') << ' ';

  bool castling = false;
  auto print_castling = [this, &oss, &castling](Piece::Color color, CastlingSide side, char piece) {
    if (this->operator[](std::pair{color, side})) {
      oss << piece;
      castling = true;
    }
  };
  print_castling(Piece::Color::WHITE, CastlingSide::KING, 'K');
  print_castling(Piece::Color::WHITE, CastlingSide::QUEEN, 'Q');
  print_castling(Piece::Color::BLACK, CastlingSide::KING, 'k');
  print_castling(Piece::Color::BLACK, CastlingSide::QUEEN, 'q');
  if (!castling) {
    oss << '-';
  }

  oss << ' ' << (en_passant_square.has_value() ? static_cast<std::string>(en_passant_square.value()) : "-");

  oss << ' ' << halfmove_count << ' ' << fullmove_count;

  return oss.str();
}

Board::OptionalPiece& Board::operator[](const Square& square) noexcept { return board[square.index]; }
const Board::OptionalPiece& Board::operator[](const Square& square) const noexcept { return board[square.index]; }

bool& Board::operator[](Board::CastlingOption option) noexcept {
  return castling_ability[static_cast<int>(option.first)][static_cast<int>(option.second)];
}
const bool& Board::operator[](Board::CastlingOption option) const noexcept {
  return castling_ability[static_cast<int>(option.first)][static_cast<int>(option.second)];
}

}  // namespace chsmv
