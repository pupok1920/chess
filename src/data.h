#ifndef __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#define __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__

#include "consts.h"
#include "pieces.h"


class Data {
public:
    Data();
    ~Data();

    const Piece *type(const PieceType&) const;

    Data& operator=(const Data&) = delete;
    Data(const Data&) = delete;

private:
    Pawn _pawn;
    Rook _rook;
    Knight _knight;
    Bishop _bishop;
    Queen _queen;
    King _king;
};
#endif // __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
