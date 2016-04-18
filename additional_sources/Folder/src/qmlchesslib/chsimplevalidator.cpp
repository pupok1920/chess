#include "chsimplevalidator.h"

#include "chpieces.h"
#include "chboarddata.h"

/*!\class ChSimpleValidator
 * \brief Implements the simple validator of chess moves.
 *
 * Does not check for castling, check, checkmate, En passant, promotion.
 *
 * Uses the data about possible moves provided by ChPiece::moves().
 */

bool ChSimpleValidator::isMoveValid(const ChBoardData *data,
    const ChSquare &from, const ChSquare &to, ChPieceColor color) const
{
    if (from == to) {
        return false;
    }

    const ChPiece* piece = data->at(from);
    if (piece->color() != color) {
        return false;
    }
    const ChPiece* target = data->at(to);

    bool result = false;
    ChSquares moves = piece->moves(from, data);
    if (std::find(moves.begin(), moves.end(), to) != moves.end()) {
        result = (target == 0) || (target->color() != color);
    }
    // TODO: check for castling, check, checkmate, En passant, promotion
    return result;
}
