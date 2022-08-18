/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "square.h"

#include <cassert>
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
  this->file = CharFileToInt(square.front());
  this->rank = CharRankToInt(square.back());
  this->index = ToIndex(this->file, this->rank);
}

Square::Square(char file, char rank)
    : file{CharFileToInt(file)}, rank{CharRankToInt(rank)}, index{ToIndex(file, rank)} {}

Square::Square(int file, int rank) : file{file}, rank{rank}, index{ToIndex(file, rank)} {}

Square::operator std::string() const noexcept {
  return {static_cast<char>(file + 'a'), static_cast<char>(7 - rank + '1')};
}

bool Square::operator==(const Square& rhs) const noexcept { return this->index == rhs.index; }
bool Square::operator!=(const Square& rhs) const noexcept { return !(*this == rhs); }

int Square::CharFileToInt(char file) noexcept {
  assert('a' <= file && file <= 'h');
  return file - 'a';
}
int Square::CharRankToInt(char rank) noexcept {
  assert('1' <= rank && rank <= '8');
  return 7 - (rank - '1');
}
int Square::ToIndex(int file, int rank) noexcept {
  assert(0 <= file && file <= 7 && 0 <= rank && rank <= 7);
  return file + rank * 8;
}
int Square::ToIndex(char file, char rank) noexcept { return ToIndex(CharFileToInt(file), CharRankToInt(rank)); }

}  // namespace chsmv
