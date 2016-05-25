#ifndef PIECES
#define PIECES
#include <cstdlib>
#include "square.h"

class Piece {
public:
    virtual ~Piece();
    virtual PieceColor color() const = 0;
    virtual QString type() const = 0;
    virtual bool moves(Square oldX, Square oldY, Square newX, Square newY) const = 0;
};

typedef std::vector<const Piece *> Pieces;

class PieceBase: public Piece {
public:
    explicit PieceBase(PieceColor color);
    PieceColor color() const;

protected:
    PieceColor _color;
};

class Pawn: public PieceBase {
public:
    explicit Pawn(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

class Rook: public PieceBase {
public:
    explicit Rook(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

class Knight: public PieceBase {
public:
    explicit Knight(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

class Bishop: public PieceBase {
public:
    explicit Bishop(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

class Queen: public PieceBase {
public:
    explicit Queen(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

class King: public PieceBase {
public:
    explicit King(PieceColor color);
    QString type() const;
    bool moves(Square oldX, Square oldY, Square newX, Square newY) const;
};

#endif // PIECES

