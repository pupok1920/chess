#include <QDebug>
#include <cstdlib>

#include "pieces.h"
#include "data.h"

Piece::Piece() {}

Piece::~Piece() {}

PieceBase::PieceBase(PieceColor color)
    :_color(color) {}

PieceColor PieceBase::color() const {
    return _color;
}

void PieceBase::diagonals(const Square &square, const Data *data, Squares &result) const {
    int r = square.row();
    int c = square.column();
    int top = std::min(r, c);
    for (int i = 1; i <= top; ++i) {
        Square sq(r - i, c - i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(r, BOARD_SIZE - 1 - c);
    for (int i = 1; i <= top; ++i) {
        Square sq(r - i, c + i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(BOARD_SIZE - r - 1, c);
    for (int i = 1; i <= top;  ++i) {
        Square sq(r + i, c - i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(BOARD_SIZE - r - 1, BOARD_SIZE - c - 1);
    for (int i = 1; i <= top; ++i) {
        Square sq(r + i, c + i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
}

void PieceBase::lines(const Square &square, const Data *data, Squares &result) const {
    for (int i = square.row() + 1; i < BOARD_SIZE; ++i) {
        Square sq(i, square.column());
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.row() - 1; i >= 0; --i) {
        Square sq(i, square.column());
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.column() + 1; i < BOARD_SIZE; ++i) {
        Square sq(square.row(), i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.column() - 1; i >= 0; --i) {
        Square sq(square.row(), i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
}

bool PieceBase::isOnBoard(int row, int column) const {
    return (row >= 0) && (row < BOARD_SIZE) && (column >= 0) && (column < BOARD_SIZE);
}

bool PieceBase::checkSquare(const Square &square, const Data *data, Squares &result) const {
    bool res = true;
    const Piece *p = data->at(square);
    if (p == nullptr) {
        result.push_back(square);
    }
    else if (p->color() != color()) {
        result.push_back(square);
        res = false;
    }
    else {
        res = false;
    }
    return res;
}

Pawn::Pawn(PieceColor color)
    :PieceBase(color) {}

PieceType Pawn::type() const {
    return PieceType::PAWN;
}

Squares Pawn::moves(const Square &square, const Data *data) const {
    Squares result;
    if (color() == PieceColor::WHITE_COLOR) {
        whiteMoves(square, data, result);
    }
    else {
        blackMoves(square, data, result);
    }
    return result;
}

void Pawn::whiteMoves(const Square &square, const Data *data, Squares &result) const {
    // move forward by one square
    Square sq(square.row() - 1, square.column());
    if (data->at(sq) == nullptr) {
        result.push_back(sq);
        // on first move it is possible to move by 2 squares
        if (square.row() == BOARD_SIZE - 2) {
            sq = Square(square.row() - 2, square.column());
            if (data->at(sq) == nullptr) {
                result.push_back(sq);
            }
        }
    }

    // capture to the left
    if (square.column() > 0) {
        sq = Square(square.row() - 1, square.column() - 1);
        const Piece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }

    // capture to the right
    if (square.column() < BOARD_SIZE - 1) {
        sq = Square(square.row() - 1, square.column() + 1);
        const Piece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }
}

void Pawn::blackMoves(const Square &square, const Data *data, Squares &result) const {
    // move forward by one square
    Square sq(square.row() + 1, square.column());
    if (data->at(sq) == nullptr) {
        result.push_back(sq);
        // on first move it is possible to move by 2 squares
        if (square.row() == 1) {
            sq = Square(square.row() + 2, square.column());
            if (data->at(sq) == nullptr) {
                result.push_back(sq);
            }
        }
    }

    // capture to the left
    if (square.column() > 0) {
        sq = Square(square.row() + 1, square.column() - 1);
        const Piece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }

    // capture to the right
    if (square.column() < BOARD_SIZE - 1) {
        sq = Square(square.row() + 1, square.column() + 1);
        const Piece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }
}

Rook::Rook(PieceColor color)
    :PieceBase(color) {}

PieceType Rook::type() const {
    return PieceType::ROOK;
}

Squares Rook::moves(const Square &square, const Data *data) const {
    Squares result;
    lines(square, data, result);
    return result;
}

Knight::Knight(PieceColor color)
    :PieceBase(color) {}

PieceType Knight::type() const {
    return PieceType::KNIGHT;
}

Squares Knight::moves(const Square &square, const Data *data) const {
    Squares result;
    static const int rows[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    static const int columns[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int r = square.row();
    int c = square.column();
    for (unsigned i = 0; i < sizeof(rows)/sizeof(rows[0]); ++i) {
        if (isOnBoard(r + rows[i], c + columns[i])) {
            Square sq(r + rows[i], c + columns[i]);
            checkSquare(sq, data, result);
        }
    }
    return result;
}

Bishop::Bishop(PieceColor color)
    :PieceBase(color) {}

PieceType Bishop::type() const {
    return PieceType::BISHOP;
}

Squares Bishop::moves(const Square &square, const Data *data) const {
    Squares result;
    diagonals(square, data, result);
    return result;
}

Queen::Queen(PieceColor color)
    :PieceBase(color) {}

PieceType Queen::type() const {
    return PieceType::QUEEN;
}

Squares Queen::moves(const Square &square, const Data *data) const {
    Squares result;
    lines(square, data, result);
    diagonals(square, data, result);
    return result;
}

King::King(PieceColor color)
    :PieceBase(color) {}

PieceType King::type() const {
    return PieceType::KING;
}

Squares King::moves(const Square &square, const Data *data) const {
    Squares result;
    static const int rows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int columns[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int r = square.row();
    int c = square.column();
    for (unsigned i = 0; i < sizeof(rows)/sizeof(rows[0]); ++i) {
        if (isOnBoard(r + rows[i], c + columns[i])) {
            Square sq(r + rows[i], c + columns[i]);
            const Piece *p = data->at(sq);
            if ((p == nullptr) || (p->color() != color())) {
                result.push_back(sq);
            }
        }
    }
    return result;
}
