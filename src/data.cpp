#include "data.h"

Data::Data() {}

Data::~Data() {}

const Piece *Data::type(PieceType pieceType) const {
    switch(pieceType) {
      case PieceType::PAWN: return &_pawn;
          break;
      case PieceType::ROOK: return &_rook;
          break;
      case PieceType::KNIGHT: return &_knight;
          break;
      case PieceType::BISHOP: return &_bishop;
          break;
      case PieceType::QUEEN: return &_queen;
          break;
      case PieceType::KING: return &_king;
          break;
      default: return nullptr;
    }
}
