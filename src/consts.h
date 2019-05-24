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
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum class RqstType {
    CONNECTION,
    MOVE
};

enum class AnswrType {
    SUCCESS,
    DENY,
    CORRECT,
    CORRECT_EN_PASSANT,
    UPDATE,
    UPDATE_EN_PASSAN
};

#endif // __CONSTSVJSNJSNJSNVSNVNSVNSLN__
