#include "chboarddata.h"

#include "chexception.h"

/*! \class ChBoardData
 * \brief Board state.
 *
 * Provides the board. It may be filled with pieces. Piece pointer may be obtained via
 * functions pawn(), king(), queen(), rook(), bishop(), knight(). Then piece may be added
 * to the board using add().
 *
 * To check the piece at specific location use at(). To remove piece from specific location use
 * remove(). To clear the board (remove all pieces) use clear().
 *
 * Never delete piece pointers. Class manages them internally.
 */

/*!
 * \brief Constructs an empty board.
 */
ChBoardData::ChBoardData()
    :_data(CH_BOARD_SIZE * CH_BOARD_SIZE, (const ChPiece*)0),
     _whitePawn(CH_WHITE_COLOR), _blackPawn(CH_BLACK_COLOR),
     _whiteKing(CH_WHITE_COLOR), _blackKing(CH_BLACK_COLOR),
     _whiteQueen(CH_WHITE_COLOR), _blackQueen(CH_BLACK_COLOR),
     _whiteRook(CH_WHITE_COLOR), _blackRook(CH_BLACK_COLOR),
     _whiteBishop(CH_WHITE_COLOR), _blackBishop(CH_BLACK_COLOR),
     _whiteKnight(CH_WHITE_COLOR), _blackKnight(CH_BLACK_COLOR)
{

}

ChBoardData::~ChBoardData()
{
    clear();
}

/*!
 * \brief Adds piece to the board.
 * \param square - location where to add piece.
 * \param piece - piece to add.
 * \exception ChLogicException is raised if \a square is not empty.
 *
 */
void ChBoardData::add(const ChSquare &square, const ChPiece *piece)
{
    CH_LOGIC_ASSERT(at(square) == 0,
        tr("Attempt to add piece to non-empty square %1:%2").arg(square.row()).arg(square.column())
    );

    _data[square.index()] = piece;
}

/// Returns piece at location \a square or 0.
const ChPiece *ChBoardData::at(const ChSquare &square) const
{
    return _data.at(square.index());
}

/*!
 * \brief Removes piece from location \a square.
 *
 * May be called for not filled square.
 *
 * \param square - location.
 *
 * \return piece that was located at \a square or 0.
 */
const ChPiece *ChBoardData::remove(const ChSquare &square)
{
    const ChPiece *result = at(square);
    _data[square.index()] = 0;
    return result;
}

/// Removes all pieces from the board.
void ChBoardData::clear()
{
    for(unsigned i = 0; i < _data.size(); ++i) {
        _data[i] = 0;
    }
}

/// Returns pointer to pawn.
const ChPiece *ChBoardData::pawn(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whitePawn : &_blackPawn;
}

/// Returns pointer to pawn king.
const ChPiece *ChBoardData::king(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whiteKing : &_blackKing;
}

/// Returns pointer to pawn queen.
const ChPiece *ChBoardData::queen(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whiteQueen : &_blackQueen;
}

/// Returns pointer to pawn rook.
const ChPiece *ChBoardData::rook(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whiteRook : &_blackRook;
}

/// Returns pointer to pawn bishop.
const ChPiece *ChBoardData::bishop(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whiteBishop : &_blackBishop;
}

/// Returns pointer to pawn knight.
const ChPiece *ChBoardData::knight(ChPieceColor color) const
{
    return (color == CH_WHITE_COLOR) ? &_whiteKnight : &_blackKnight;
}

