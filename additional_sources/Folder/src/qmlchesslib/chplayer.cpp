#include "chplayer.h"

/*!
 * \class ChPlayer
 * \brief Interface for Player.
 *
 * Each player should implement setBoardData(), startMove() and
 * stopMove().
 *
 * Player should emit signal \ref moved() to perform the move. Player may emit signal
 * \ref selectionChanged() to update selection indication on board.
 *
 * Examples of possible players:
 * - Human player (see \ref ChHumanPlayer)
 * - Computer player
 * - Remote network player
 * - etc.
 */

/*! \fn ChPlayer::setBoardData(const ChBoardData *boardData)
 * \brief Called to provide to the Player the reference to board data.
 * \param boardData - reference to board data.
 */

/*! \fn ChPlayer::startMove()
 * \brief Called to inform Player that it is time to perform move.

 When move is ready then the signal moved() should be emitted by the Player.
 */

/*! \fn ChPlayer::stopMove()
 * \brief Called to inform Player that it should stop thinking about move.

 After stopMove() call the Player should not emit selectionChanged() and moved() signals.
 */

/*! \fn ChPlayer::moved(int from, int to)
 * \brief Signal to inform about move.
 *
 * The signal should be emitted by the Player to provide data about the move.
 * \param from - index to move piece from. See \ref ChSquare about indexes.
 * \param to - index to move piece from.
 */

/*! \fn ChPlayer::selectionChanged(int selected, const ChSquares &highlighted)
 * \brief Signal to inform about piece selected to move.
 *
 * The signal may be emitted by the Player to provide information about possible piece moves.
 * \param selected - index of the piece to move or -1.
 * \param highlighted - indexes of possible move target squares.
 */

/*!
 * \brief Destructor.
 *
 * Does nothing.
 *
 */

ChPlayer::~ChPlayer()
{

}

