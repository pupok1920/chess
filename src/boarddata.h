#ifndef BOARDDATA
#define BOARDDATA
#include <QCoreApplication>
#include "pieces.h"

class BoardData {
public:
    BoardData();
    ~BoardData();
    void add(const Square &square, const Piece *piece);
    void remove(const Square &square);
    const Piece *at(const Square &square) const;

    const Piece *pawn(PieceColor color) const;
    const Piece *rook(PieceColor color) const;
    const Piece *knight(PieceColor color) const;
    const Piece *bishop(PieceColor color) const;
    const Piece *queen(PieceColor color) const;
    const Piece *king(PieceColor color) const;

private:
    Q_DISABLE_COPY(BoardData)
    Pieces _data;
    Pawn _whitePawn;
    Pawn _blackPawn;
    Rook _whiteRook;
    Rook _blackRook;
    Knight _whiteKnight;
    Knight _blackKnight;
    Bishop _whiteBishop;
    Bishop _blackBishop;
    Queen _whiteQueen;
    Queen _blackQueen;
    King _whiteKing;
    King _blackKing;
};

#endif // BOARDDATA

