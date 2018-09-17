#include "pieces.h"

Piece::Piece() {}

Piece::~Piece() {}

PieceBase::PieceBase(PieceColor color): _color(color) {}

PieceColor PieceBase::color() const {
    return _color;
}

Pawn::Pawn(PieceColor color):PieceBase(color) {}

QString Pawn::type() const {
    return "pawn";
}

bool Pawn::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldY - newY) != 1 || abs(oldX - newX) > 1)
        return false;
    else
        return true;
}

Rook::Rook(PieceColor color):PieceBase(color) {}

QString Rook::type() const {
    return "rook";
}

bool Rook::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if((abs(oldX - newX) >= 1 && (oldY - newY) != 0)
            || (abs(oldY - newY) >= 1 && (oldX - newX) != 0))
        return false;
    else
        return true;
}

Knight::Knight(PieceColor color):PieceBase(color) {}

QString Knight::type() const {
    return "knight";
}

bool Knight::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(!((abs(oldX - newX) == 2 && abs(oldY - newY) == 1)
            || (abs(oldY - newY) == 2 && abs(oldX - newX) == 1)))
        return false;
    else
        return true;
}

Bishop::Bishop(PieceColor color):PieceBase(color) {}

QString Bishop::type() const {
    return "bishop";
}

bool Bishop::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldX - newX) != abs(oldY - newY))
        return false;
    else
        return true;
}

Queen::Queen(PieceColor color):PieceBase(color) {}

QString Queen::type() const {
    return "queen";
}

bool Queen::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(((abs(oldX - newX) >= 1 && (oldY - newY) != 0)
        || (abs(oldY - newY) >= 1 && (oldX - newX) != 0))
                || (abs(oldX - newX) != abs(oldY - newY)))
        return true;
    else
        return false;
}

King::King(PieceColor color):PieceBase(color) {}

QString King::type() const {
    return "king";
}

bool King::isMoveValid(int oldX, int oldY, int newX, int newY) const {
    if(abs(oldX - newX) > 1 || abs(oldY - newY) > 1)
        return false;
    else
        return true;
}

