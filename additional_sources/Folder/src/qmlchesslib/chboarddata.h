#ifndef CHBOARDDATA_H
#define CHBOARDDATA_H

#include <QCoreApplication>

#include "chlib.h"
#include "chpieces.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChBoardData
{
    Q_DECLARE_TR_FUNCTIONS(ChBoardData)
public:
    ChBoardData();
    ~ChBoardData();
    void add(const ChSquare &square, const ChPiece *piece);
    const ChPiece *at(const ChSquare &square) const;
    const ChPiece *remove(const ChSquare &square);

    void clear();

    const ChPiece *pawn(ChPieceColor color) const;
    const ChPiece *king(ChPieceColor color) const;
    const ChPiece *queen(ChPieceColor color) const;
    const ChPiece *rook(ChPieceColor color) const;
    const ChPiece *bishop(ChPieceColor color) const;
    const ChPiece *knight(ChPieceColor color) const;
private:
    Q_DISABLE_COPY(ChBoardData)
    /// Squares on board. _data[i] == 0 if square is empty.
    ChPieces _data;
    ChPawn _whitePawn;
    ChPawn _blackPawn;
    ChKing _whiteKing;
    ChKing _blackKing;
    ChQueen _whiteQueen;
    ChQueen _blackQueen;
    ChRook _whiteRook;
    ChRook _blackRook;
    ChBishop _whiteBishop;
    ChBishop _blackBishop;
    ChKnight _whiteKnight;
    ChKnight _blackKnight;
};

#endif // CHBOARDDATA_H
