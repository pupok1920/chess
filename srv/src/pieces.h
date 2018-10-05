#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#include <cstdlib>

class Piece {
public:
    explicit Piece();
    virtual ~Piece();
    virtual bool isMoveValid(int oldX, int oldY, int newX, int newY) const = 0;

    Piece& operator=(Piece const&) = delete;
    Piece(Piece const&) = delete;
};

class Pawn: public Piece {
public:
    explicit Pawn();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Rook: public Piece {
public:
    explicit Rook();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Knight: public Piece {
public:
    explicit Knight();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Bishop: public Piece {
public:
    explicit Bishop();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class Queen: public Piece {
public:
    explicit Queen();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

class King: public Piece {
public:
    explicit King();
    bool isMoveValid(int oldX, int oldY, int newX, int newY) const override;
};

#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__

