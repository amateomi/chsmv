/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "move.h"

#include <regex>
#include <sstream>
#include <stdexcept>

namespace chsmv {

Move::Move(std::string_view move) try : origin{move.substr(0, 2)}, destination{move.substr(2, 2)} {
  if (!std::regex_match(std::string{move}, std::regex{"([a-h][1-8]){2}[qrbn]?"})) {
    throw std::exception{};
  }
  switch (move.back()) {
    case 'q':
      this->promotion = Promotion::TO_QUEEN;
      break;
    case 'r':
      this->promotion = Promotion::TO_ROOK;
      break;
    case 'b':
      this->promotion = Promotion::TO_BISHOP;
      break;
    case 'n':
      this->promotion = Promotion::TO_KNIGHT;
      break;
    default:
      this->promotion = Promotion::NONE;
      break;
  }
} catch (const std::exception& e) {
  throw std::domain_error{'\"' + std::string{move} + '\"' +
                          " is invalid move notation\n"
                          "Right notation: <move descriptor> = <from square><to square>[<promoted to>]\n"
                          "Example: e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)"};
}

Move::operator std::string() const noexcept {
  std::ostringstream oss;
  oss << static_cast<std::string>(origin) << static_cast<std::string>(destination);
  switch (promotion) {
    case Promotion::TO_QUEEN:
      oss << 'q';
      break;
    case Promotion::TO_ROOK:
      oss << 'r';
      break;
    case Promotion::TO_BISHOP:
      oss << 'b';
      break;
    case Promotion::TO_KNIGHT:
      oss << 'n';
      break;
    case Promotion::NONE:
      break;
  }
  return oss.str();
}

int Move::FileDirection() const noexcept { return destination.rank - origin.rank > 0 ? 1 : -1; }
int Move::RankDirection() const noexcept { return destination.file - origin.file > 0 ? 1 : -1; }

}  // namespace chsmv
