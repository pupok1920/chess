#include "chvalidator.h"

/*!
 * \class ChValidator
 *
 * \brief Validates moves on chess board.
 *
 * Provides interface for classes responcible for validation of chess moves on board.
 *
 * Function isMoveValid() is called every time when validator user wants to check the move.
 *
 * Validator implementation may use the data about possible moves provided by ChPiece::moves()
 * function but it is not mandatory. For example, trivial implementation (all moves are allowed)
 * also may be useful for some tasks.
 *
 * \ref ChBoardModel is the main user of the validator. It looks reasonable that \ref ChPlayer
 * implementations also use the same validator as \ref ChBoardModel but it is not a requirement.
 */

/*! \fn bool ChValidator::isMoveValid(const ChBoardData *data, const ChSquare &from, const ChSquare& to, ChPieceColor color) const
 * \brief Returns \a true if move is possible, \a false otherwise.
 * \param data - board data.
 * \param from - square to move from.
 * \param to - square to move to.
 * \param color - color of the Player that performs the move.
 */

/*!
 * \brief Destructor.
 *
 * Does nothing.
 */
ChValidator::~ChValidator()
{

}

