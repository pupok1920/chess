#include "pieces.h"

Piece::~Piece() {}

PieceBase::PieceBase(PieceColor color): _color(color) {}

PieceColor PieceBase::color() const {
    return _color;
}

Pawn::Pawn(PieceColor color):PieceBase(color) {}

Pawn::source(PieceColor color) const {
    switch (color) {
    case WHITE_COLOR:
        return "src/pawn_white.png";
    case BLACK_COLOR:
        return "src/queen_black.png";
    }
}

Rook::Rook(PieceColor color):PieceBase(color) {}

Rook::source(PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/rook_white.png";
   case BLACK_COLOR:
       return "src/rook_black.png";
   }
}

Knight::Knight(PieceColor color):PieceBase(color) {}

Knight::source(PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/";
   case BLACK_COLOR:
       return "src/";
   }
}

Bishop::Bishop(PieceColor color):PieceBase(color) {}

Bishop::source(PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/knight_white.png";
   case BLACK_COLOR:
       return "src/knight_black.png";
   }
}

Queen::Queen(PieceColor color):PieceBase(color) {}

Queen::source(PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/queen_white.png";
   case BLACK_COLOR:
       return "src/queen_black.png";
   }
}

King::King(PieceColor color):PieceBase(color) {}

King::source(PieceColor color) const {
   switch (color) {
   case WHITE_COLOR:
       return "src/king_white.png";
   case BLACK_COLOR:
       return "src/king_black.png";
   }
}

