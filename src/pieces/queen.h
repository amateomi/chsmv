/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_PIECES_QUEEN_H_
#define CHSMV_SRC_PIECES_QUEEN_H_

#include "bishop.h"
#include "rook.h"

namespace chsmv {

class Queen : public Rook, public Bishop {
 public:
  Queen(const Square& position, Color color) : Piece{position, color}, Rook{position, color}, Bishop{position, color} {}
  ~Queen() override = default;

  [[nodiscard]] Conditions GetMoveConditions(const Move& move) const noexcept override;
  [[nodiscard]] Conditions GetCaptureConditions(const Move& move) const noexcept override;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECES_QUEEN_H_
