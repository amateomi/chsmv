/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_PIECE_H_
#define CHSMV_SRC_PIECE_H_

#include <memory>
#include <vector>

#include "square.h"

namespace chsmv {

enum class Color { WHITE, BLACK };
enum class CastlingAbility { AVAILABLE, UNAVAILABLE };

struct CastlingRights {
  CastlingAbility white_king_side;
  CastlingAbility white_queen_side;
  CastlingAbility black_king_side;
  CastlingAbility black_queen_side;
};

using EmptySquares = std::vector<Square>;
using Conditions = std::tuple<EmptySquares, CastlingRights>;

class Move;

class Piece {
 public:
  Piece(const Square& position, Color color) : position_{position}, color_{color} {};
  virtual ~Piece() = default;

  static std::unique_ptr<Piece> MakePiece(char piece, const Square& position);

  [[nodiscard]] const Square& GetPosition() const noexcept;
  [[nodiscard]] Color GetColor() const noexcept;

  [[nodiscard]] virtual Conditions GetMoveConditions(const Move& move) const noexcept = 0;
  [[nodiscard]] virtual Conditions GetCaptureConditions(const Move& move) const noexcept = 0;

 protected:
  Square position_;
  chsmv::Color color_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECE_H_
