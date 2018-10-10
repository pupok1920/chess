#ifndef __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#define __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#include <QCoreApplication>

#include "consts.h"
#include "pieces.h"


class Data {
public:
    Data();
    ~Data();

    const Piece *type(PieceType pieceType) const;

    Data& operator=(Data const&) = delete;
    Data(Data const&) = delete;

private:
    Pawn _pawn;
    Rook _rook;
    Knight _knight;
    Bishop _bishop;
    Queen _queen;
    King _king;
};

#endif // __DataNJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__

