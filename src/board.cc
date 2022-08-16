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

    std::string board;
    iss >> board;
    auto file{'a'};
    auto rank{'8'};
    for (auto item : board) {
      if (file > 'h' && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        --rank;
        file = 'a';
      } else if (std::isdigit(item)) {
        file = static_cast<char>(file + (item - '0'));
      } else {
        this->board_[Square{file, rank}.index] = Piece::Factory(item);
        ++file;
      }
    }

    std::string turn;
    iss >> turn;
    this->move_turn_ = turn == "w" ? MoveTurn::WHITE : MoveTurn::BLACK;

    std::string castling;
    iss >> castling;
    auto get_availability = [&castling](auto piece) -> bool { return castling.find(piece) != std::string::npos; };
    this->castling_ability_[WHITE][KING] = get_availability('K');
    this->castling_ability_[WHITE][QUEEN] = get_availability('Q');
    this->castling_ability_[BLACK][KING] = get_availability('k');
    this->castling_ability_[BLACK][QUEEN] = get_availability('q');

    std::string en_passant;
    iss >> en_passant;
    this->en_passant_square_ = en_passant == "-" ? std::nullopt : std::make_optional<Square>(en_passant);

    iss >> this->halfmove_count_ >> this->fullmove_count_;
    if (this->halfmove_count_ > 50) {
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

  for (auto i{0}; i < size_; ++i) {
    if (i % 8 == 0 && i != 0) {
      oss << '/';
    }
    if (board_[i].has_value()) {
      oss << static_cast<char>(board_[i].value());
    } else {
      auto empty_squares_count = 1;
      while (i % 8 != 7) {
        if (board_[i + 1].has_value()) {
          break;
        }
        ++empty_squares_count;
        ++i;
      }
      oss << empty_squares_count;
    }
  }

  oss << ' ' << (move_turn_ == MoveTurn::WHITE ? 'w' : 'b') << ' ';

  if ((!castling_ability_[WHITE][KING] && !castling_ability_[WHITE][QUEEN]) &&
      (!castling_ability_[BLACK][KING] && !castling_ability_[BLACK][QUEEN])) {
    oss << '-';
  } else {
    if (castling_ability_[WHITE][KING]) {
      oss << 'K';
    }
    if (castling_ability_[WHITE][QUEEN]) {
      oss << 'Q';
    }
    if (castling_ability_[BLACK][KING]) {
      oss << 'k';
    }
    if (castling_ability_[BLACK][QUEEN]) {
      oss << 'q';
    }
  }

  oss << ' ' << (en_passant_square_.has_value() ? static_cast<std::string>(en_passant_square_.value()) : "-");

  oss << ' ' << halfmove_count_ << ' ' << fullmove_count_;

  return oss.str();
}

}  // namespace chsmv
