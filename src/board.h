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
  // Constants
  static constexpr auto file_size{8};
  static constexpr auto rank_size{8};
  static constexpr auto size{file_size * rank_size};
  static constexpr auto start_board_position_in_fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
  static constexpr std::string_view castling_chars_in_fen{"KQkq"};

  // Types
  using OptionalPiece = std::optional<Piece>;
  enum class CastlingSide : int { KING, QUEEN };

  // Constructors
  explicit Board(std::string_view board_in_fen = start_board_position_in_fen);

  // Operators
  explicit operator std::string() const noexcept;

  OptionalPiece& operator[](int index) noexcept;
  const OptionalPiece& operator[](int index) const noexcept;
  OptionalPiece& operator[](const Square& square) noexcept;
  const OptionalPiece& operator[](const Square& square) const noexcept;

  // Functions
  bool& GetCastling(Piece::Color color, CastlingSide side) noexcept;
  [[nodiscard]] const bool& GetCastling(Piece::Color color, CastlingSide side) const noexcept;

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
  std::array<OptionalPiece, size> squares;
  std::array<bool, 4> castling_ability{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
