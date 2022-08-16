/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "piece.h"

#include <cctype>
#include <stdexcept>

namespace chsmv {

Piece Piece::Factory(char piece) {
  Color color = isupper(piece) ? Color::WHITE : Color::BLACK;
  piece = static_cast<char>(tolower(piece));
  switch (piece) {
    case 'k':
      return Piece{color, Piece::Type::KING};
    case 'q':
      return Piece{color, Piece::Type::QUEEN};
    case 'r':
      return Piece{color, Piece::Type::ROOK};
    case 'b':
      return Piece{color, Piece::Type::BISHOP};
    case 'n':
      return Piece{color, Piece::Type::KNIGHT};
    case 'p':
      return Piece{color, Piece::Type::PAWN};
    default:
      throw std::domain_error('\"' + std::string{piece} + '\"' +
                              " is invalid piece character\n"
                              "Available characters: 'k', 'q', 'r', 'b', 'n', 'p' in lower or upper cases");
  }
}

Piece::operator char() const noexcept {
  char piece;
  switch (type) {
    case Type::KING:
      piece = 'k';
      break;
    case Type::QUEEN:
      piece = 'q';
      break;
    case Type::ROOK:
      piece = 'r';
      break;
    case Type::BISHOP:
      piece = 'b';
      break;
    case Type::KNIGHT:
      piece = 'n';
      break;
    case Type::PAWN:
      piece = 'p';
      break;
  }
  return color == Color::WHITE ? static_cast<char>(toupper(piece)) : static_cast<char>(piece);
}

}  // namespace chsmv
