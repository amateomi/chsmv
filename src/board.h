#ifndef CHSMV_SRC_BOARD_H_
#define CHSMV_SRC_BOARD_H_

#include <memory>
#include <optional>
#include <set>

#include "piece.h"

namespace chsmv {

constexpr auto kSquaresOnBoard = 64;
constexpr auto kStartBoard{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

class Board {
 public:
  explicit Board(const std::string& board = kStartBoard);

  explicit operator std::string() const noexcept;

  [[nodiscard]] std::optional<const Piece*> GetPiece(const Square& square) const noexcept;

  [[nodiscard]] bool IsMeetCondition(const Conditions& conditions) const noexcept;

  [[nodiscard]] Board MakeMove(const Move& move) const;

 private:
  std::set<std::unique_ptr<Piece>> pieces_;

  Color move_side_;
  CastlingAbility castling_ability_;
  Square en_passant_target_;

  int halfmove_clock_;
  int fullmove_counter_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
