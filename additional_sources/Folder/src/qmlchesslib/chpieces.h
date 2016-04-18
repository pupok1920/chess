#ifndef CHPIECES_H
#define CHPIECES_H

#include <vector>

#include <QCoreApplication>

#include "chlib.h"
#include "chconsts.h"
#include "chsquare.h"

class ChBoardData;

class QMLCHESSLIB_COMMON_DLLSPEC ChPiece
{
public:
    virtual ~ChPiece();
    virtual ChPieceColor color() const = 0;
    virtual QString type() const = 0;
    virtual ChSquares moves(const ChSquare &square, const ChBoardData *data) const = 0;
};

typedef std::vector<const ChPiece *> ChPieces;

class QMLCHESSLIB_COMMON_DLLSPEC ChPieceBase: public ChPiece
{
    Q_DECLARE_TR_FUNCTIONS(ChPieceBase)
public:
    explicit ChPieceBase(ChPieceColor color);
    ChPieceColor color() const;

protected:
    void diagonals(const ChSquare &square, const ChBoardData *data, ChSquares &result) const;
    void lines(const ChSquare &square, const ChBoardData *data, ChSquares &result) const;
    bool isOnBoard(int row, int column) const;
    bool checkSquare(const ChSquare &square, const ChBoardData *data, ChSquares &result) const;
    void verifyColor(const ChSquare &square, const ChBoardData *data) const;

private:
    ChPieceColor _color;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChPawn: public ChPieceBase
{
    Q_DECLARE_TR_FUNCTIONS(ChPawn)
public:
    explicit ChPawn(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;

private:
    void whiteMoves(const ChSquare &square, const ChBoardData *data, ChSquares &result) const;
    void blackMoves(const ChSquare &square, const ChBoardData *data, ChSquares &result) const;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChKing: public ChPieceBase
{
public:
    explicit ChKing(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChRook: public ChPieceBase
{
public:
    explicit ChRook(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChBishop: public ChPieceBase
{
public:
    explicit ChBishop(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChQueen: public ChPieceBase
{
public:
    explicit ChQueen(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChKnight: public ChPieceBase
{
public:
    explicit ChKnight(ChPieceColor color);
    ChSquares moves(const ChSquare &square, const ChBoardData *data) const;
    QString type() const;
};

#endif // CHPIECES_H
