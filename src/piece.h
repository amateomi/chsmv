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
  static std::unique_ptr<Piece> MakePiece(char piece, const Square& position);

  Piece(const Square& position, Color color);
  virtual ~Piece() = default;

  [[nodiscard]] const Square& GetPosition() const;
  [[nodiscard]] Color GetColor() const;

  [[nodiscard]] virtual Conditions GetMoveConditions(const Move& move) const = 0;
  [[nodiscard]] virtual Conditions GetCaptureConditions(const Move& move) const = 0;

 private:
  Square position_;
  chsmv::Color color_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_PIECE_H_
