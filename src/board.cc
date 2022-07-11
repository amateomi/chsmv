#include "board.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <regex>

namespace chsmv {

Board::Board(const std::string& fen) {
  try {
    std::regex re{"([kqrbnpKQRBNP1-8]{1,8}/){7}[kqrbnpKQRBNP1-8]{1,8} [wb] (-|(K?Q?k?q?)) (-|[a-h][36])( [0-9]*){2}"};
    if (!std::regex_match(fen, re)) {
      throw std::exception{};
    }
    std::vector<std::string> words;
    std::istringstream iss{fen};
    std::string buffer;
    while (std::getline(iss, buffer, ' ')) {
      words.push_back(std::move(buffer));
    }

    char file{'a'};
    char rank{'8'};
    for (auto item : words[0U]) {
      if (file > 'h' && item != '/') {
        throw std::exception{};
      }
      if (item == '/') {
        --rank;
        file = 'a';
      } else if (std::isdigit(item)) {
        file = static_cast<char>(file + (item - '1'));
      } else {
        Square square{file, rank};
        auto new_piece = pieces_.insert(Piece::MakePiece(item, square)).first;
        squares_[static_cast<int>(square)] = std::make_optional<const Piece*>(new_piece->get());
        ++file;
      }
    }

    move_side_ = words[1U] == "w" ? Color::WHITE : Color::BLACK;

    auto get_availability = [&words](char piece) {
      return words[2U].find(piece) == std::string::npos ? CastlingAbility::UNAVAILABLE : CastlingAbility::AVAILABLE;
    };
    castling_.white_king_side = get_availability('K');
    castling_.white_queen_side = get_availability('Q');
    castling_.black_king_side = get_availability('k');
    castling_.black_queen_side = get_availability('q');

    en_passant_ = words[3U] == "-" ? std::nullopt : std::make_optional<Square>(words[3U]);

    halfmove_clock_ = std::stoi(words[4U]);
    if (halfmove_clock_ > 50) {
      throw std::exception{};
    }

    fullmove_counter_ = std::stoi(words[5U]);

  } catch (const std::exception&) {
    throw std::domain_error('\"' + fen + '\"' +
                            " is invalid FEN board\n"
                            "Right FEN: <FEN> = <Piece Placement> <Side to move> <Castling ability> <En passant target "
                            "square> <Halfmove clock> <Fullmove counter>\n"
                            "Example: " +
                            kStartBoard);
  }
}

Board::operator std::string() const noexcept {}

std::optional<const Piece*> Board::GetPiece(const Square& square) const noexcept {}

bool Board::IsMeetCondition(const Conditions& conditions) const noexcept { return false; }

Board Board::MakeMove(const Move& move) const {}

}  // namespace chsmv
