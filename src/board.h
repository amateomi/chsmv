/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_BOARD_H_
#define CHSMV_SRC_BOARD_H_

#include <array>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

#include "piece.h"
#include "square.h"

namespace chsmv {

class Board {
 public:  // Types
  enum MoveTurn { WHITE, BLACK };
  enum CastlingSide { KING, QUEEN };

 public:  // Methods
  explicit Board(std::string_view board_in_fen = start_board_position_in_fen_);

  explicit operator std::string() const noexcept;

 private:  // Constants
  static constexpr auto file_size_{8};
  static constexpr auto rank_size_{8};
  static constexpr auto size_{file_size_ * rank_size_};
  static constexpr auto start_board_position_in_fen_{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

 private:  // Fields
  /**
   * @note Indexing starts from a8 to h1:\n
   *     a  b  c  d  e  f  g  h \n
   * 8 | 0| 1| 2| 3|..|..|..|..|\n
   * 7 | 8| 9|..|..|..|..|..|..|\n
   * 6 |..|..|..|..|..|..|..|..|\n
   * 5 |..|..|..|..|..|..|..|..|\n
   * 4 |..|..|..|..|..|..|..|..|\n
   * 3 |..|..|..|..|..|..|..|..|\n
   * 2 |..|..|..|..|..|..|..|..|\n
   * 1 |..|..|..|..|..|..|..|63|\n
   */
  std::array<std::optional<Piece>, size_> board_;
  MoveTurn move_turn_;
  std::array<std::array<bool, 2>, 2> castling_ability_{};
  std::optional<Square> en_passant_square_;
  int halfmove_count_{};
  int fullmove_count_{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
