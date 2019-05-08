#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__

#include "consts.h"
#include "square.h"

class Data;

class Piece {
public:
    Piece();
    virtual ~Piece();
    virtual PieceColor color() const = 0;
    virtual Squares moves(const Square &, const Data *) const = 0;

    Piece& operator=(Piece const&) = delete;
    Piece(Piece const&) = delete;
};

class PieceBase: public Piece {
public:
    explicit PieceBase(PieceColor color);
    PieceColor color() const;

protected:
    void diagonals(const Square &, const Data *, Squares &) const;
    void lines(const Square &, const Data *, Squares &) const;
    bool checkSquare(const Square &, const Data *, Squares &) const;
    bool isOnBoard(int, int) const;

private:
    PieceColor _color;
};

class Pawn: public PieceBase {
public:
    explicit Pawn(PieceColor color);
    Squares moves(const Square &, const Data *) const override;

private:
    void whiteMoves(const Square &, const Data *, Squares &) const;
    void blackMoves(const Square &, const Data *, Squares &) const;
};

class Rook: public PieceBase {
public:
    explicit Rook(PieceColor color);
    Squares moves(const Square &, const Data *) const override;
};

class Knight: public PieceBase {
public:
    explicit Knight(PieceColor color);
    Squares moves(const Square &, const Data *) const override;
};

class Bishop: public PieceBase {
public:
    explicit Bishop(PieceColor color);
    Squares moves(const Square &, const Data *) const override;
};

class Queen: public PieceBase {
public:
    explicit Queen(PieceColor color);
    Squares moves(const Square &, const Data *) const override;
};

class King: public PieceBase {
public:
    explicit King(PieceColor color);
    Squares moves(const Square &, const Data *) const override;
};
#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
