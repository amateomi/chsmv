#ifndef CHSMV_SRC_PIECES_BISHOP_H_
#define CHSMV_SRC_PIECES_BISHOP_H_

#include "../piece.h"

namespace chsmv {

class Bishop : public virtual Piece {
 public:
  Bishop(const Square& position, Color color) : Piece{position, color} {}
  ~Bishop() override = default;

  [[nodiscard]] Conditions GetMoveConditions(const Move& move) const noexcept override;
  [[nodiscard]] Conditions GetCaptureConditions(const Move& move) const noexcept override;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECES_BISHOP_H_
