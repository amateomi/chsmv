/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "square.h"

#include <regex>

namespace chsmv {

Square::Square(const std::string& square) {
  if (!std::regex_match(square, std::regex{"[a-h][1-8]"})) {
    throw std::domain_error{'\"' + square + '\"' +
                            " is invalid square notation\n"
                            "Right notation: <square> = <file letter><rank number>\n"
                            "Example: a1, e4, h8"};
  }
  position_ = square.front() - 'a' + (square.back() - '1') * 8;
}

Square::Square(char file, char rank) : Square(std::string{file, rank}) {}

Square::operator std::string() const noexcept { return {GetFileChar(), GetRankChar()}; }
Square::operator int() const noexcept { return position_; }

int Square::GetFile() const noexcept { return position_ % 8; }
char Square::GetFileChar() const noexcept { return static_cast<char>(GetFile() + 'a'); }

int Square::GetRank() const noexcept { return position_ / 8; }
char Square::GetRankChar() const noexcept { return static_cast<char>(GetRank() + '1'); }

}  // namespace chsmv
