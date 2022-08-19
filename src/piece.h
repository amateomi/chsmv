/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_PIECE_H_
#define CHSMV_SRC_PIECE_H_

namespace chsmv {

struct Piece {
  // Type
  enum class Color : int { WHITE, BLACK };
  enum class Type { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

  // Methods
  [[nodiscard]] static Piece Factory(char piece);

  explicit operator char() const noexcept;

  // Fields
  Color color;
  Type type;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECE_H_
