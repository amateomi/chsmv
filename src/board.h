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

struct Board {
  // Types
  using OptionalPiece = std::optional<Piece>;
  enum class CastlingSide : int { KING, QUEEN };
  using CastlingOption = std::pair<Piece::Color, CastlingSide>;

  // Constructor
  explicit Board(std::string_view board_in_fen = start_board_position_in_fen);

  // Operators
  explicit operator std::string() const noexcept;

  OptionalPiece& operator[](const Square& square) noexcept;
  const OptionalPiece& operator[](const Square& square) const noexcept;

  bool& operator[](CastlingOption option) noexcept;
  const bool& operator[](CastlingOption option) const noexcept;

  // Constants
  static constexpr auto file_size{8};
  static constexpr auto rank_size{8};
  static constexpr auto size{file_size * rank_size};
  static constexpr auto start_board_position_in_fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

  // Data
 public:
  Piece::Color move_turn;
  std::optional<Square> en_passant_square;
  int halfmove_count{};
  int fullmove_count{};

 private:
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
  std::array<OptionalPiece, size> board;
  std::array<std::array<bool, 2>, 2> castling_ability{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
