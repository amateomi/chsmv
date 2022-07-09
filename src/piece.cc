#include "piece.h"

namespace chsmv {

Piece::Piece(const Square& position, chsmv::Color color) : position_{position}, color_{color} {}

std::unique_ptr<Piece> Piece::MakePiece(char piece, const Square& position) { return {}; }

const Square& Piece::GetPosition() const { return position_; }
Color Piece::GetColor() const { return color_; }

}  // namespace chsmv
