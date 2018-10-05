#include "data.h"

Data::Data() {}

Data::~Data() {}

const Piece *Data::type(PieceType pieceType) const {
    switch(pieceType) {
        case 1: return &_pawn;
            break;
        case 2: return &_rook;
            break;
        case 3: return &_knight;
            break;
        case 4: return &_bishop;
            break;
        case 5: return &_queen;
            break;
        case 6: return &_king;
            break;
    }
}
