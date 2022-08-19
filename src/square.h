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

class Square {
 public:
  // Constants
  static constexpr auto total_files_{8};
  static constexpr auto total_ranks_{8};
  static constexpr auto total_squares_{total_files_ * total_ranks_};

  // Constructors
  Square() = default;
  explicit Square(std::string_view square);
  Square(int file, int rank);

  // Operators
  explicit operator std::string() const noexcept;

  bool operator==(const Square& rhs) const noexcept;
  bool operator!=(const Square& rhs) const noexcept;

  /// Iterate from a8 to h1. Do nothing if equals to last square
  void operator++() noexcept;

  // Functions
  [[nodiscard]] int GetFile() const noexcept;
  [[nodiscard]] int GetRank() const noexcept;
  [[nodiscard]] int GetIndex() const noexcept;

  void SetFile(int file) noexcept;
  void SetRank(int rank) noexcept;

 private:
  // Data
  int file_{};
  int rank_{};
};

}  // namespace chsmv

#endif  // CHSMV_SRC_SQUARE_H_
