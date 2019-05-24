#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#include <cstdlib>

#include "square.h"

class Piece {
public:
    Piece();
    virtual ~Piece();
    virtual PieceColor color() const = 0;
    virtual QString type() const = 0;

    Piece& operator=(const Piece&) = delete;
    Piece(const Piece&) = delete;
};

class PieceBase: public Piece {
public:
    explicit PieceBase(PieceColor);
    PieceColor color() const override;

protected:
    PieceColor _color;
};

class Pawn: public PieceBase {
public:
    explicit Pawn(PieceColor);
    QString type() const override;
};

class Rook: public PieceBase {
public:
    explicit Rook(PieceColor);
    QString type() const override;
};

class Knight: public PieceBase {
public:
    explicit Knight(PieceColor);
    QString type() const override;
};

class Bishop: public PieceBase {
public:
    explicit Bishop(PieceColor);
    QString type() const override;
};

class Queen: public PieceBase {
public:
    explicit Queen(PieceColor);
    QString type() const override;
};

class King: public PieceBase {
public:
    explicit King(PieceColor);
    QString type() const override;
};
#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
