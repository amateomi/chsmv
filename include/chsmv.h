/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_INCLUDE_CHSMV_H_
#define CHSMV_INCLUDE_CHSMV_H_

#include <string>
#include <string_view>
#include <vector>

namespace chsmv {

enum class MoveStatus { VALID, INVALID };

class ChessMoveAnalyzer {
 public:
  [[nodiscard]] MoveStatus CheckMove(std::string_view board_in_fen, std::string_view move_in_lan) const;

  [[nodiscard]] std::string MakeMove(std::string_view board_in_fen, std::string_view move_in_lan) const;

  [[nodiscard]] std::vector<bool> GetAvailableMoves(std::string_view board_in_fen, std::string_view square) const;
};

}  // namespace chsmv

#endif  // CHSMV_INCLUDE_CHSMV_H_
