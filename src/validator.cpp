#include <QDebug>

#include "validator.h"
#include "pieces.h"
#include "data.h"

Validator::Validator()
        :_enPassantSquare(0),
         _enPassantPiece(0) {}

Validator::~Validator() {}

bool Validator::findIn(const Squares &squares, const Square &square) const {
    return std::find(squares.begin(), squares.end(), square) != squares.end();
}

bool Validator::isPawnMoveValid(const Squares &moves, const Square &from, const Square &to) {
    // if Pawn captures En Passant
    if((_enPassantSquare == to.index())
            && (std::abs(to.row() - from.row()) == 1)
            && (std::abs(to.column() - from.column()) == 1)) {
                _enPassantSquare = 0;
                return true;
    }
    // if Pawn does double move
     if(from.row() == 1 || from.row() == 6) {
        if((std::abs(to.row() - from.row()) == 2) && isOrdinaryMoveValid(moves, to)) {
            _enPassantSquare = (from < to) ? (from.index() + BOARD_SIZE) : (from.index() - BOARD_SIZE);
            _enPassantPiece = to.index();
            return true;
        }
    }
    // if Pawn does ordinary move
    if(isOrdinaryMoveValid(moves, to)) {
        _enPassantSquare = 0;
        _enPassantPiece = 0;
        return true;
    }
    return false;
}

bool Validator::isOrdinaryMoveValid(const Squares &moves, const Square &to) {
    return std::find(moves.begin(), moves.end(), to) != moves.end();
}

bool Validator::isEnPassantPossible() const {
    return (_enPassantPiece > 0 && _enPassantSquare == 0);
}

// return _enPassantPiece value and reset it
int Validator::getEnPassantPiece() {
    int tmp = _enPassantPiece;
    _enPassantPiece = 0;
    return tmp;
}
