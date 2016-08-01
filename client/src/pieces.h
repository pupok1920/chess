#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#include <cstdlib>
#include "square.h"


class Piece {
public:
    virtual ~Piece();
    virtual PieceColor color() const = 0;
    virtual QString type() const = 0;
    virtual bool isMoveValid(int oldX, int oldY, int newX, int newY) const = 0;

    //see "mayers. more effective c++".
    //Piece operator = (Piece const&) = delete;
    //Piece(Piece&) = delete;
};

class PieceBase: public Piece {
public:
    explicit PieceBase(PieceColor color);
    PieceColor color() const override;

protected:
    PieceColor _color;
};

class Pawn: public PieceBase {
public:
    explicit Pawn(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Rook: public PieceBase {
public:
    explicit Rook(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Knight: public PieceBase {
public:
    explicit Knight(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Bishop: public PieceBase {
public:
    explicit Bishop(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Queen: public PieceBase {
public:
    explicit Queen(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class King: public PieceBase {
public:
    explicit King(PieceColor color);
    QString type() const override;
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__

