#ifndef CHSMV_SRC_PIECES_KING_H_
#define CHSMV_SRC_PIECES_KING_H_

#include "../piece.h"

namespace chsmv {

class King : public Piece {
 public:
  King(const Square& position, Color color) : Piece{position, color} {}
  ~King() override = default;

  [[nodiscard]] Conditions GetMoveConditions(const Move& move) const noexcept override;
  [[nodiscard]] Conditions GetCaptureConditions(const Move& move) const noexcept override;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECES_KING_H_
