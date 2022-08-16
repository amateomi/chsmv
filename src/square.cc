/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "square.h"

#include <regex>
#include <stdexcept>

namespace chsmv {

Square::Square(std::string_view square) {
  if (!std::regex_match(std::string{square}, std::regex{"[a-h][1-8]"})) {
    throw std::domain_error{'\"' + std::string{square} + '\"' +
                            " is invalid square notation\n"
                            "Right notation: <square> = <file letter><rank number>\n"
                            "Example: a1, e4, h8"};
  }
  this->file = square.front() - 'a';
  this->rank = 7 - (square.back() - '1');
  this->index = this->file + this->rank * 8;
}

Square::Square(char file, char rank) {
  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    throw std::domain_error{'\"' + std::string{file, rank} + '\"' +
                            " is invalid square notation\n"
                            "Right notation: <square> = <file letter><rank number>\n"
                            "Example: a1, e4, h8"};
  }
  this->file = file - 'a';
  this->rank = 7 - (rank - '1');
  this->index = this->file + this->rank * 8;
}

Square::operator std::string() const noexcept { return {static_cast<char>(file + 'a'), static_cast<char>(7 - (rank - '1'))}; }

}  // namespace chsmv
