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
  enum class CastlingSide : int { SHORT, LONG };

  // Constructors
  explicit Board(std::string_view board_in_fen = start_board_position_in_fen_);

  // Operators
  explicit operator std::string() const noexcept;

  OptionalPiece& operator[](int index) noexcept;
  const OptionalPiece& operator[](int index) const noexcept;
  OptionalPiece& operator[](const Square& square) noexcept;
  const OptionalPiece& operator[](const Square& square) const noexcept;

  // Functions
  [[nodiscard]] Piece::Color& MoveTurn() noexcept;
  [[nodiscard]] Piece::Color MoveTurn() const noexcept;

  bool& Castling(Piece::Color color, CastlingSide side) noexcept;
  [[nodiscard]] bool Castling(Piece::Color color, CastlingSide side) const noexcept;

  [[nodiscard]] std::optional<Square>& EnPassantSquare() noexcept;
  [[nodiscard]] const std::optional<Square>& EnPassantSquare() const noexcept;

  int& Halfmove() noexcept;
  [[nodiscard]] int Halfmove() const noexcept;

  int& Fullmove() noexcept;
  [[nodiscard]] int Fullmove() const noexcept;

 private:
  // Data
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
  Piece::Color move_turn_;
  std::array<bool, 4> castling_ability_{};
  std::optional<Square> en_passant_square_;
  int halfmove_count_{};
  int fullmove_count_{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
