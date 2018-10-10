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

Rook::Rook(PieceColor color):PieceBase(color) {}

QString Rook::type() const {
    return "rook";
}

Knight::Knight(PieceColor color):PieceBase(color) {}

QString Knight::type() const {
    return "knight";
}

Bishop::Bishop(PieceColor color):PieceBase(color) {}

QString Bishop::type() const {
    return "bishop";
}

Queen::Queen(PieceColor color):PieceBase(color) {}

QString Queen::type() const {
    return "queen";
}

King::King(PieceColor color):PieceBase(color) {}

QString King::type() const {
    return "king";
}
