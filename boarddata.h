#ifndef BOARDDATA
#define BOARDDATA
#include "pieces.h"

class BoardData {
private:
    BoardData();
    ~BoardData();
    void add(const Square &square, const Piece *piece);
    const Piece *at(const Square &square) const;

    const Piece *pawn(PieceColor color) const;
    const Piece *rook(PieceColor color) const;
    const Piece *knight(PieceColor color) const;
    const Piece *bishop(PieceColor color) const;
    const Piece *queen(PieceColor color) const;
    const Piece *king(PieceColor color) const;

private:
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

