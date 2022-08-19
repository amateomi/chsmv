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
  file_ = square.front() - 'a';
  rank_ = total_ranks_ - 1 - (square.back() - '1');
}

Square::Square(int file, int rank) : file_{file}, rank_{rank} {}

Square::operator std::string() const noexcept {
  return {static_cast<char>(GetFile() + 'a'), static_cast<char>(total_ranks_ - 1 - GetRank() + '1')};
}

bool Square::operator==(const Square& rhs) const noexcept {
  return this->file_ == rhs.file_ && this->rank_ == rhs.rank_;
}
bool Square::operator!=(const Square& rhs) const noexcept { return !(*this == rhs); }

void Square::operator++() noexcept {
  if (file_ == total_files_ - 1) {
    if (rank_ == total_ranks_ - 1) {
      return;
    }
    file_ = 0;
    ++rank_;
  } else {
    ++file_;
  }
}

int Square::GetFile() const noexcept { return file_; }
int Square::GetRank() const noexcept { return rank_; }
int Square::GetIndex() const noexcept { return file_ + rank_ * 8; }

void Square::SetFile(int file) noexcept {
  assert(0 <= file && file < total_files_);
  file_ = file;
}
void Square::SetRank(int rank) noexcept {
  assert(0 <= rank && rank < total_ranks_);
  rank_ = rank;
}

}  // namespace chsmv
