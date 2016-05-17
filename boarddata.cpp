#include "boarddata.h"

BoardData::BoardData()
    :_data(BOARD_SIZE * BOARD_SIZE,(const Piece*)0),
    _whitePawn(WHITE_COLOR), _blackPawn(BLACK_COLOR),
    _whiteRook(WHITE_COLOR), _blackRook(BLACK_COLOR),
    _whiteKnight(WHITE_COLOR), _blackKnight(BLACK_COLOR),
    _whiteBishop(WHITE_COLOR), _blackBishop(BLACK_COLOR),
    _whiteQueen(WHITE_COLOR), _blackQueen(BLACK_COLOR),
    _whiteKing(WHITE_COLOR), _blackKing(BLACK_COLOR) {}

BoardData::~BoardData() {}

void BoardData::add(const Square &square, const Piece *piece) {
    _data[square.index()] = piece;
}

const Piece *BoardData::at(const ChSquare &square) const {
    return _data.at(square.index());
}

const Piece *BoardData::pawn(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whitePawn : &_blackPawn;
}

const Piece *BoardData::rook(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whiteRook : &_blackRook;
}

const Piece *BoardData::knight(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whiteKnight : &_blackKnight;
}

const Piece *BoardData::bishop(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whiteBishop : &_blackBishop;
}

const Piece *BoardData::queen(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whiteQueen : &_blackQueen;
}

const Piece *BoardData::king(PieceColor color) const {
    return (color == WHITE_COLOR) ? &_whiteKing : &_blackKing;
}
