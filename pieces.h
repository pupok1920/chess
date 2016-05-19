#ifndef PIECES
#define PIECES
#include "square.h"

class Piece {
public:
    virtual ~Piece();
    virtual PieceColor color() const = 0;
    virtual QString source(const PieceColor color) const = 0;
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
    QString source(const PieceColor color) const;
};

class Rook: public PieceBase {
public:
    explicit Rook(PieceColor color);
    QString source(const PieceColor color) const;
};

class Knight: public PieceBase {
public:
    explicit Knight(PieceColor color);
    QString source(const PieceColor color) const;
};

class Bishop: public PieceBase {
public:
    explicit Bishop(PieceColor color);
    QString source(const PieceColor color) const;
};

class Queen: public PieceBase {
public:
    explicit Queen(PieceColor color);
    QString source(const PieceColor color) const;
};

class King: public PieceBase {
public:
    explicit King(PieceColor color);
    QString source(const PieceColor color) const;
};

#endif // PIECES

