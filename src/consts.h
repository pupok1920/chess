#ifndef __CONSTSVJSNJSNJSNVSNVNSVNSLN__
#define __CONSTSVJSNJSNJSNVSNVNSVNSLN__

enum {
    BOARD_SIZE = 8
};

enum class PieceColor {
    WHITE_COLOR,
    BLACK_COLOR
};

enum class PieceType {
    PAWN = 1,
    ROOK = 2,
    KNIGHT = 3,
    BISHOP = 4,
    QUEEN = 5,
    KING = 6
};

enum class RqstType {
    CONNECTION,
    MOVE
};

enum class AnswrType {
    SUCCESS,
    DENY,
    CORRECT,
    UPDATE
};

#endif // __CONSTSVJSNJSNJSNVSNVNSVNSLN__
