#include "board.h"

#include <algorithm>
#include <cctype>
#include <regex>

namespace chsmv {

Board::Board(const std::string& board) {
  try {
    std::regex re{"([kqrbnpKQRBNP1-8]{1,8}/){7}[kqrbnpKQRBNP1-8]{1,8} [wb] (-|(K?Q?k?q?)) (-|[a-h][36])( [0-9]*){2}"};
    if (!std::regex_match(board, re)) {
      throw std::exception{};
    }
    auto whitespace = board.begin() + static_cast<long>(board.find_first_of(' '));
    char rank = '8';
    char file = 'a';
    auto piece_generator = [this, &rank, &file](char item) {
      if (file > 'h' && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        --rank;
        file = 'a';
      } else if (std::isdigit(item)) {
        file = static_cast<char>(file + (item - '1'));
      } else {
        (void)pieces_.insert(Piece::MakePiece(item, Square{file, rank}));
        file++;
      }
    };
    (void)std::for_each(board.begin(), whitespace, piece_generator);

  } catch (const std::exception&) {
    throw std::domain_error("");
  }
}

Board::operator std::string() const noexcept { return std::string(); }

std::optional<const Piece*> Board::GetPiece(const Square& square) const noexcept {}

bool Board::IsMeetCondition(const Conditions& conditions) const noexcept { return false; }

Board Board::MakeMove(const Move& move) const {}

}  // namespace chsmv
