#ifndef __BOARDDATANJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#define __BOARDDATANJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__
#include <QCoreApplication>
#include "pieces.h"


class BoardData {
public:
    BoardData();
    ~BoardData();
    void add(const Square &square, const Piece *piece);
    void remove(const Square &square);
    const Piece *at(const Square &square) const;

    void clear();

    const Piece *pawn(PieceColor color) const;
    const Piece *rook(PieceColor color) const;
    const Piece *knight(PieceColor color) const;
    const Piece *bishop(PieceColor color) const;
    const Piece *queen(PieceColor color) const;
    const Piece *king(PieceColor color) const;

private:
    Q_DISABLE_COPY(BoardData)

    typedef std::vector<const Piece *> Pieces;
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

#endif // __BOARDDATANJGDNBSLNDSGNBDJKNBDNBDGKJBNDKJF__

