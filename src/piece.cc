/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "piece.h"

#include <stdexcept>

#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"

namespace chsmv {

std::unique_ptr<Piece> Piece::MakePiece(char piece, const Square& position) {
  std::string available_characters{"kqrbnpKQRBNP"};
  if (available_characters.find(piece) == std::string::npos) {
    throw std::domain_error('\"' + std::string{piece} + '\"' +
                            " is invalid piece character\n"
                            "Available characters: " +
                            available_characters);
  }
  Color color{std::isupper(piece) ? Color::WHITE : Color::BLACK};
  switch (static_cast<char>(std::tolower(piece))) {
    case 'k':
      return std::make_unique<King>(position, color);

    case 'q':
      return std::make_unique<Queen>(position, color);

    case 'r':
      return std::make_unique<Rook>(position, color);

    case 'b':
      return std::make_unique<Bishop>(position, color);

    case 'n':
      return std::make_unique<Knight>(position, color);

    case 'p':
      return std::make_unique<Pawn>(position, color);

    default:
      break;
  }
}

const Square& Piece::GetPosition() const noexcept { return position_; }
Color Piece::GetColor() const noexcept { return color_; }

}  // namespace chsmv
