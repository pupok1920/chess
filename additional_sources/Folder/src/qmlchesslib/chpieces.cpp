#include "chpieces.h"

#include "chexception.h"
#include "chboarddata.h"

/*! \class ChPiece
 * \brief Base class for all pieces on board.
 *
 * Each piece should provide information about color(). For identification in QML piece
 * provides string type().
 *
 * Also piece should provide information about possible moves via moves()
 * call. \ref ChSimpleValidator and \ref ChHumanPlayer use this information, but in general
 * player (inherited from \ref ChPlayer) and/or validator (inherited from \ref ChValidator) may
 * not use this function and follow the own rules.
 *
 * Piece implements pattern \b FlyWeight. Piece does not store it's coordinates but uses
 * information provided via parameters of moves() call.
 *
*/

/*!  \fn ChPieceColor ChPiece::color() const
 * \brief Returns color of the piece.
 */

/*!  \fn ChPieceColor ChPiece::type() const
 * \brief Returns string presentation of the piece type.
 *
 * Used in QML.
 */


/*!  \fn ChSquares ChPiece::moves(const ChSquare &square, const ChBoardData *data) const
 * \brief Returns possible moves.
 *
 * \param square - square to move from.
 * \param data - information about location of other pieces on board.
 */

/*!
 * \brief Destructor.
 *
 * Does nothing.
 *
 */
ChPiece::~ChPiece()
{

}

/*! \class ChPieceBase
 * \brief Provides utility functions.
  */

ChPieceBase::ChPieceBase(ChPieceColor color):_color(color)
{

}

ChPieceColor ChPieceBase::color() const
{
    return _color;
}

/*!
 * \brief Finds possible moves by diagonal.
 * \param square - square to move from.
 * \param data - information about location of other pieces on board.
 * \param result - all possible diagonal target squares are added to this parameter.
 */
void ChPieceBase::diagonals(const ChSquare &square, const ChBoardData *data,
    ChSquares &result) const
{
    int r = square.row();
    int c = square.column();
    int top = std::min(r, c);
    for (int i = 1; i <= top; ++i) {
        ChSquare sq(r - i, c - i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(r, CH_BOARD_SIZE - 1 - c);
    for (int i = 1; i <= top; ++i) {
        ChSquare sq(r - i, c + i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(CH_BOARD_SIZE - r - 1, c);
    for (int i = 1; i <= top;  ++i) {
        ChSquare sq(r + i, c - i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    top = std::min(CH_BOARD_SIZE - r - 1, CH_BOARD_SIZE - c - 1);
    for (int i = 1; i <= top; ++i) {
        ChSquare sq(r + i, c + i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
}

/*!
 * \brief Finds possible moves by lines (horizontal and vertical).
 * \param square - square to move from.
 * \param data - information about location of other pieces on board.
 * \param result - all possible diagonal target squares are added to this parameter.
 */
void ChPieceBase::lines(const ChSquare &square, const ChBoardData *data, ChSquares &result) const
{
    for (int i = square.row() + 1; i < CH_BOARD_SIZE; ++i) {
        ChSquare sq(i, square.column());
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.row() - 1; i >= 0; --i) {
        ChSquare sq(i, square.column());
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.column() + 1; i < CH_BOARD_SIZE; ++i) {
        ChSquare sq(square.row(), i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
    for (int i = square.column() - 1; i >= 0; --i) {
        ChSquare sq(square.row(), i);
        if (!checkSquare(sq, data, result)) {
            break;
        }
    }
}

/*!
 * \brief Returns true if square is on board.
 * \param row - square row (starting from 0).
 * \param column - square column (starting from 0).
 * \return \a true if square is on board, \a false otherwise.
 */
bool ChPieceBase::isOnBoard(int row, int column) const
{
    return (row >= 0) && (row < CH_BOARD_SIZE) && (column >= 0) && (column < CH_BOARD_SIZE);
}

/*!
 * \brief Checks is it possible to move to the square.
 * \param square - target square.
 * \param data - information about location of other pieces on board.
 * \param result - add square to this parameter if it is possible to move to it.
 * \return \a true if square is empty or occuped by the piece of opposite color, \a false otherwise.
 */
bool ChPieceBase::checkSquare(const ChSquare &square, const ChBoardData *data,
    ChSquares &result) const
{
    bool res = true;
    const ChPiece *p = data->at(square);
    if (p == 0) {
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

void ChPieceBase::verifyColor(const ChSquare &square, const ChBoardData *data) const
{
    const ChPiece* p = data->at(square);
    CH_LOGIC_ASSERT(p != 0, tr("Attempt to move from empty square %1").arg(square.index()));
    CH_LOGIC_ASSERT(p->color() == color(), tr("Object for different color is used at %1")
        .arg(square.index()));
    CH_LOGIC_ASSERT(p->type() == type(), tr("Object for different type is used at %1")
        .arg(square.index()));
}

ChPawn::ChPawn(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChPawn::moves(const ChSquare &square, const ChBoardData *data) const
{
    verifyColor(square, data);
    ChSquares result;
    if (color() == CH_WHITE_COLOR) {
        whiteMoves(square, data, result);
    }
    else {
        blackMoves(square, data, result);
    }
    return result;
}

QString ChPawn::type() const
{
    return "pawn";
}

void ChPawn::whiteMoves(const ChSquare &square, const ChBoardData *data, ChSquares &result) const
{
    CH_LOGIC_ASSERT(square.row() != 0,
        tr("Bad position of Pawn at %1:%2").arg(square.row()).arg(square.column())
    );

    if (square.row() == CH_BOARD_SIZE - 1) {
        //TODO: Change when promotion is implemented
        return;
    }

    // move forward by one square
    ChSquare sq(square.row() + 1, square.column());
    if (data->at(sq) == 0) {
        result.push_back(sq);
        // on first move it is possible to move by 2 squares
        if (square.row() == 1) {
            sq = ChSquare(square.row() + 2, square.column());
            if (data->at(sq) == 0) {
                result.push_back(sq);
            }
        }
    }

    // capture to the left
    if (square.column() > 0) {
        sq = ChSquare(square.row() + 1, square.column() - 1);
        const ChPiece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }

    // capture to the right
    if (square.column() < CH_BOARD_SIZE - 1) {
        sq = ChSquare(square.row() + 1, square.column() + 1);
        const ChPiece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }
}

void ChPawn::blackMoves(const ChSquare &square, const ChBoardData *data, ChSquares &result) const
{
    CH_LOGIC_ASSERT(square.row() != CH_BOARD_SIZE - 1,
        tr("Bad position of Pawn at %1:%2").arg(square.row()).arg(square.column())
    );

    if (square.row() == 0) {
        //TODO: Change when promotion is implemented
        return;
    }

    // move forward by one square
    ChSquare sq(square.row() - 1, square.column());
    if (data->at(sq) == 0) {
        result.push_back(sq);
        // on first move it is possible to move by 2 squares
        if (square.row() == CH_BOARD_SIZE - 2) {
            sq = ChSquare(square.row() - 2, square.column());
            if (data->at(sq) == 0) {
                result.push_back(sq);
            }
        }
    }

    // capture to the left
    if (square.column() > 0) {
        sq = ChSquare(square.row() - 1, square.column() - 1);
        const ChPiece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }

    // capture to the right
    if (square.column() < CH_BOARD_SIZE - 1) {
        sq = ChSquare(square.row() - 1, square.column() + 1);
        const ChPiece *p = data->at(sq);
        if (p && (p->color() != color())) {
            result.push_back(sq);
        }
    }
}

ChKing::ChKing(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChKing::moves(const ChSquare &square, const ChBoardData *data) const
{
     verifyColor(square, data);
     ChSquares result;
     static const int rows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
     static const int columns[] = {-1, 0, 1, -1, 1, -1, 0, 1};
     int r = square.row();
     int c = square.column();
     for (unsigned i = 0; i < sizeof(rows)/sizeof(rows[0]); ++i) {
         if (isOnBoard(r + rows[i], c + columns[i])) {
             ChSquare sq(r + rows[i], c + columns[i]);
             const ChPiece *p = data->at(sq);
             if ((p == 0) || (p->color() != color())) {
                result.push_back(sq);
             }
         }
     }
     // TODO: Add castling
     return result;
}

QString ChKing::type() const
{
    return "king";
}


ChRook::ChRook(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChRook::moves(const ChSquare &square, const ChBoardData *data) const
{
    verifyColor(square, data);
    ChSquares result;
    lines(square, data, result);
    return result;
}

QString ChRook::type() const
{
    return "rook";
}


ChBishop::ChBishop(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChBishop::moves(const ChSquare &square, const ChBoardData *data) const
{
    verifyColor(square, data);
    ChSquares result;
    diagonals(square, data, result);
    return result;
}

QString ChBishop::type() const
{
    return "bishop";
}

ChQueen::ChQueen(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChQueen::moves(const ChSquare &square, const ChBoardData *data) const
{
    verifyColor(square, data);
    ChSquares result;
    lines(square, data, result);
    diagonals(square, data, result);
    return result;
}

QString ChQueen::type() const
{
    return "queen";
}


ChKnight::ChKnight(ChPieceColor color):ChPieceBase(color)
{

}

ChSquares ChKnight::moves(const ChSquare &square, const ChBoardData *data) const
{
    verifyColor(square, data);
    ChSquares result;
    static const int rows[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    static const int columns[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int r = square.row();
    int c = square.column();
    for (unsigned i = 0; i < sizeof(rows)/sizeof(rows[0]); ++i) {
        if (isOnBoard(r + rows[i], c + columns[i])) {
            ChSquare sq(r + rows[i], c + columns[i]);
            checkSquare(sq, data, result);
        }
    }
    return result;
}

QString ChKnight::type() const
{
    return "knight";
}
