/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_BOARD_H_
#define CHSMV_SRC_BOARD_H_

#include <array>
#include <optional>
#include <set>

#include "piece.h"

namespace chsmv {

constexpr auto kSquaresOnBoard = 64;
constexpr auto kStartBoard{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

class Board {
 public:
  explicit Board(const std::string& fen = kStartBoard);

  explicit operator std::string() const noexcept;

  [[nodiscard]] std::optional<const Piece*> GetPiece(const Square& square) const noexcept;

  [[nodiscard]] bool IsMeetCondition(const Conditions& conditions) const noexcept;

  [[nodiscard]] Board MakeMove(const Move& move) const;

 private:
  std::set<std::unique_ptr<Piece>> pieces_;
  std::array<std::optional<const Piece*>, kSquaresOnBoard> squares_;

  Color move_side_;
  CastlingRights castling_{};
  std::optional<Square> en_passant_;

  int halfmove_clock_;
  int fullmove_counter_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_BOARD_H_
