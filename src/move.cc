#include "move.h"

#include <regex>

namespace chsmv {

Move::Move(const std::string& move) try : origin_{move.substr(0U, 2U)}, destination_{move.substr(2U, 2U)} {
  if (!std::regex_match(move, std::regex{"([a-h][1-8]){2}[qrbn]?"})) {
    throw std::exception{};
  }
  switch (move.back()) {
    case 'q':
      promotion_ = Promotion::TO_QUEEN;
      break;

    case 'r':
      promotion_ = Promotion::TO_ROOK;
      break;

    case 'b':
      promotion_ = Promotion::TO_BISHOP;
      break;

    case 'n':
      promotion_ = Promotion::TO_KNIGHT;
      break;

    default:
      promotion_ = Promotion::NONE;
      break;
  }
} catch (const std::exception&) {
  throw std::domain_error{'\"' + move + '\"' +
                          "is invalid move notation\n"
                          "Right notation: <move descriptor> = <from square><to square>[<promoted to>]\n"
                          "Example: e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)"};
}

Move::operator std::string() const noexcept {
  auto result{static_cast<std::string>(origin_) + static_cast<std::string>(destination_)};
  switch (promotion_) {
    case Promotion::TO_QUEEN:
      result += 'q';
      break;

    case Promotion::TO_ROOK:
      result += 'r';
      break;

    case Promotion::TO_BISHOP:
      result += 'b';
      break;

    case Promotion::TO_KNIGHT:
      result += 'n';
      break;

    case Promotion::NONE:
      break;
  }
  return result;
}

const chsmv::Square& chsmv::Move::GetOrigin() const noexcept { return origin_; }
const chsmv::Square& chsmv::Move::GetDestination() const noexcept { return destination_; }
const Promotion& chsmv::Move::GetPromotion() const noexcept { return promotion_; }

}  // namespace chsmv
