#include "pieces.h"

Piece::Piece() {}

Piece::~Piece() {}

Pawn::Pawn():Piece() {}

bool Pawn::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldY - newY) != 1 || abs(oldX - newX) > 1)
        return false;
    else
        return true;
}

Rook::Rook():Piece() {}

bool Rook::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if((abs(oldX - newX) >= 1 && (oldY - newY) != 0)
            || (abs(oldY - newY) >= 1 && (oldX - newX) != 0))
        return false;
    else
        return true;
}

Knight::Knight():Piece() {}

bool Knight::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(!((abs(oldX - newX) == 2 && abs(oldY - newY) == 1)
            || (abs(oldY - newY) == 2 && abs(oldX - newX) == 1)))
        return false;
    else
        return true;
}

Bishop::Bishop():Piece() {}

bool Bishop::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldX - newX) != abs(oldY - newY))
        return false;
    else
        return true;
}

Queen::Queen():Piece() {}

bool Queen::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(!((abs(oldX - newX) == abs(oldY - newY))
        || (abs(oldX - newX) >= 1 && (oldY - newY) == 0)
           || (abs(oldY - newY) >= 1 && (oldX - newX) == 0)))
        return false;
    else
        return true;
}

King::King():Piece() {}

bool King::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldX - newX) > 1 || abs(oldY - newY) > 1)
        return false;
    else
        return true;
}
