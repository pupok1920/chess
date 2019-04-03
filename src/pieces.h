#ifndef __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
#define __PIECESFJULVFJNSJKLSNJSKLVNVNSL__

class Piece {
public:
    Piece();
    virtual ~Piece();
    virtual bool isMoveValid(int, int, int, int) = 0;

    Piece& operator=(Piece const&) = delete;
    Piece(Piece const&) = delete;
};

class Pawn: public Piece {
public:
    Pawn();
    bool isMoveValid(int, int, int, int) override;

private:
    bool isFirstMove();
    void setFirstMoveState(bool);

private:
    bool _firstMove;
};

class Rook: public Piece {
public:
    Rook();
    bool isMoveValid(int, int, int, int) override;
};

class Knight: public Piece {
public:
    Knight();
    bool isMoveValid(int, int, int, int) override;
};

class Bishop: public Piece {
public:
    Bishop();
    bool isMoveValid(int, int, int, int) override;
};

class Queen: public Piece {
public:
    Queen();
    bool isMoveValid(int, int, int, int) override;
};

class King: public Piece {
public:
    King();
    bool isMoveValid(int, int, int, int) override;
};
#endif // __PIECESFJULVFJNSJKLSNJSKLVNVNSL__
