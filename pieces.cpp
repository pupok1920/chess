#include "pieces.h"

Piece::~Piece() {}

PieceBase::PieceBase(PieceColor color): _color(color) {}

PieceColor PieceBase::color() const {
    return _color;
}

Pawn::Pawn(PieceColor color):PieceBase(color) {}

QString Pawn::source(const PieceColor color) const {
    switch (color) {
    case WHITE_COLOR:
        return "src/pawn_white.png";
        break;
    case BLACK_COLOR:
        return "src/pawn_black.png";
        break;
    default:
        return "";
    }
}

Rook::Rook(PieceColor color):PieceBase(color) {}

QString Rook::source(const PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/rook_white.png";
       break;
   case BLACK_COLOR:
       return "src/rook_black.png";
       break;
   default:
       return "";
   }
}

Knight::Knight(PieceColor color):PieceBase(color) {}

QString Knight::source(const PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/knight_white.png";
       break;
   case BLACK_COLOR:
       return "src/knight_black.png";
       break;
   default:
       return "";
   }
}

Bishop::Bishop(PieceColor color):PieceBase(color) {}

QString Bishop::source(const PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/bishop_white.png";
       break;
   case BLACK_COLOR:
       return "src/bishop_black.png";
       break;
   default:
       return "";
   }
}

Queen::Queen(PieceColor color):PieceBase(color) {}

QString Queen::source(const PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/queen_white.png";
       break;
   case BLACK_COLOR:
       return "src/queen_black.png";
       break;
   default:
       return "";
   }
}

King::King(PieceColor color):PieceBase(color) {}

QString King::source(const PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/king_white.png";
       break;
   case BLACK_COLOR:
       return "src/king_black.png";
       break;
   default:
       return "";
   }
}

