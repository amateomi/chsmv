/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_SQUARE_H_
#define CHSMV_SRC_SQUARE_H_

#include <string>
#include <string_view>

namespace chsmv {

struct Square {
  // Constructors
  explicit Square(std::string_view square);
  Square(char file, char rank);
  Square(int file, int rank);

  // Operators
  explicit operator std::string() const noexcept;

  bool operator==(const Square& rhs) const noexcept;
  bool operator!=(const Square& rhs) const noexcept;

  // Functions
  static int CharFileToInt(char file) noexcept;
  static int CharRankToInt(char rank) noexcept;
  static int ToIndex(int file, int rank) noexcept;
  static int ToIndex(char file, char rank) noexcept;

  // Fields
  int file;
  int rank;
  int index;  //!< @note Indexing starts from a8 to h1
};

}  // namespace chsmv

#endif  // CHSMV_SRC_SQUARE_H_
