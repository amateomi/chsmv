/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CHSMV_SRC_SQUARE_H_
#define CHSMV_SRC_SQUARE_H_

#include <string>

namespace chsmv {

class Square {
 public:
  explicit Square(const std::string& square);

  explicit operator std::string() const noexcept;

  [[nodiscard]] int GetFile() const noexcept;
  [[nodiscard]] char GetFileChar() const noexcept;
  [[nodiscard]] int GetRank() const noexcept;
  [[nodiscard]] char GetRankChar() const noexcept;

 private:
  int position_;
};

}  // namespace chsmv

#endif  // CHSMV_SRC_SQUARE_H_
