#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#include <cstdlib>

class Piece {
public:
    Piece();
    virtual ~Piece();
    virtual bool isMoveValid(int oldX, int oldY, int newX, int newY) const = 0;

    Piece& operator=(Piece const&) = delete;
    Piece(Piece const&) = delete;
};

class Pawn: public Piece {
public:
    Pawn();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Rook: public Piece {
public:
    Rook();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Knight: public Piece {
public:
    Knight();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Bishop: public Piece {
public:
    Bishop();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Queen: public Piece {
public:
    Queen();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class King: public Piece {
public:
    King();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__

