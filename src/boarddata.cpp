#include "boarddata.h"

BoardData::BoardData()
    :_setOfPieces(BOARD_SIZE * BOARD_SIZE,(const Piece*)nullptr),
    _whitePawn(PieceColor::WHITE_COLOR), _blackPawn(PieceColor::BLACK_COLOR),
    _whiteRook(PieceColor::WHITE_COLOR), _blackRook(PieceColor::BLACK_COLOR),
    _whiteKnight(PieceColor::WHITE_COLOR), _blackKnight(PieceColor::BLACK_COLOR),
    _whiteBishop(PieceColor::WHITE_COLOR), _blackBishop(PieceColor::BLACK_COLOR),
    _whiteQueen(PieceColor::WHITE_COLOR), _blackQueen(PieceColor::BLACK_COLOR),
    _whiteKing(PieceColor::WHITE_COLOR), _blackKing(PieceColor::BLACK_COLOR) {}

BoardData::~BoardData() {}

void BoardData::add(const Square &square, const Piece *piece) {
    _setOfPieces[square.index()] = piece;
}

void BoardData::remove(const Square &square) {
    _setOfPieces[square.index()] = nullptr;
}

const Piece *BoardData::at(const Square &square) const {
    return _setOfPieces.at(square.index());
}

void BoardData::clear() {
    for(unsigned i = 0; i < _setOfPieces.size(); ++i) {
        _setOfPieces[i] = nullptr;
    }
}

const Piece *BoardData::pawn(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whitePawn : &_blackPawn;
}

const Piece *BoardData::rook(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whiteRook : &_blackRook;
}

const Piece *BoardData::knight(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whiteKnight : &_blackKnight;
}

const Piece *BoardData::bishop(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whiteBishop : &_blackBishop;
}

const Piece *BoardData::queen(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whiteQueen : &_blackQueen;
}

const Piece *BoardData::king(PieceColor color) const {
    return (color == PieceColor::WHITE_COLOR) ? &_whiteKing : &_blackKing;
}
