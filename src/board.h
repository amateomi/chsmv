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
 public:
  // Constants
  static constexpr auto start_board_position_in_fen_{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
  static constexpr std::string_view castling_chars_in_fen_{"KQkq"};

  // Types
  using OptionalPiece = std::optional<Piece>;
  enum class CastlingSide : int { KING, QUEEN };

  // Constructors
  explicit Board(std::string_view board_in_fen = start_board_position_in_fen_);

  // Operators
  explicit operator std::string() const noexcept;

  OptionalPiece& operator[](int index) noexcept;
  const OptionalPiece& operator[](int index) const noexcept;
  OptionalPiece& operator[](const Square& square) noexcept;
  const OptionalPiece& operator[](const Square& square) const noexcept;

  // Functions
  [[nodiscard]] Piece::Color GetMoveTurn() const noexcept;

  [[nodiscard]] const std::optional<Square>& GetEnPassantSquare() const noexcept;

  bool& Castling(Piece::Color color, CastlingSide side) noexcept;
  [[nodiscard]] const bool& Castling(Piece::Color color, CastlingSide side) const noexcept;

 private:
  // Data
  Piece::Color move_turn_;
  std::optional<Square> en_passant_square_;
  int halfmove_count_{};
  int fullmove_count_{};
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
  std::array<OptionalPiece, Square::total_squares_> squares_;
  std::array<bool, 4> castling_ability_{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
