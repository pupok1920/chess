#include "chmovecommand.h"

#include "chboarddata.h"
#include "chexception.h"

/*! \class ChMoveCommand
 * \brief Data about one move.
 */

/*!
 * \brief ChMoveCommand::ChMoveCommand
 * \param data - chess board.
 * \param from - square to move from.
 * \param to - square to move to.
 * \param parent - parent command.
 */

ChMoveCommand::ChMoveCommand(ChBoardData *data, const ChSquare &from, const ChSquare &to,
    QUndoCommand *parent):QUndoCommand(parent), _data(data), _from(from), _to(to), _removedPiece(0)
{
}

ChMoveCommand::~ChMoveCommand()
{
}

/*!
 * \brief Performs move.
 * \exception ChLogicException if no piece at \a from position (see
 * \ref ChMoveCommand::ChMoveCommand()).
 */
void ChMoveCommand::redo()
{
    // make sure that the command is executable before board modifications
    const ChPiece *cur = _data->at(_from);
    CH_LOGIC_ASSERT(cur != 0, tr("Attempt to move from empty cell %1").arg(_from.index()));

    _removedPiece = _data->remove(_to);
    _data->remove(_from);
    _data->add(_to, cur);
}

/*!
 * \brief Undo the move.
 * \exception ChLogicException if no piece at \a to position (see
 * \ref ChMoveCommand::ChMoveCommand()) or piece at \a from position.
 */
void ChMoveCommand::undo()
{
    // make sure that the command is executable before board modifications
    const ChPiece *cur = _data->at(_to);
    CH_LOGIC_ASSERT(cur != 0, tr("Attempt to undo move from empty cell %1").arg(_to.index()));
    _data->add(_from, cur);

    _data->remove(_to);
    _data->add(_to, _removedPiece);
    _removedPiece = 0;
}

ChSquare ChMoveCommand::from() const
{
    return _from;
}

ChSquare ChMoveCommand::to() const
{
    return _to;
}
