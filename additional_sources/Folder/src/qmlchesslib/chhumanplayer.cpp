#include "chhumanplayer.h"

#include <algorithm>

#include "chboarddata.h"
#include "chvalidator.h"
#include "chexception.h"

/*! \class ChHumanPlayer
 * \brief Human player
 *
 * Implements interface \ref ChPlayer. In addition to that interface provides the following
 * methods to support interaction with user:
 * - setValidator() allows to specify validator of moves.
 * - onSquareClicked() slot may be connected to the signal that informs about user clicks on board.
 *
 */

/*!
 * \brief Creates Human player for specified \a color.
 */
ChHumanPlayer::ChHumanPlayer(ChPieceColor color)
  :ChPlayer(), _data(0), _inMove(false), _validator(0), _color(color)
{

}

ChHumanPlayer::~ChHumanPlayer()
{

}

void ChHumanPlayer::setBoardData(const ChBoardData *boardData)
{
    _data = boardData;
}

void ChHumanPlayer::startMove()
{
    _inMove = true;
    emit selectionChanged(-1, ChSquares());
}

void ChHumanPlayer::stopMove()
{
    _inMove = false;
}

/*!
 * \brief Sets validator to use in possible moves selection.
 * \param validator - validator.
 */
void ChHumanPlayer::setValidator(const ChValidator *validator)
{
    _validator = validator;
}

struct Ch_MoveChecker: public std::unary_function<ChSquare, bool> {
    Ch_MoveChecker(const ChValidator *v,
        const ChBoardData *data,
        const ChSquare &from,
        ChPieceColor color)
        :_v(v),
        _data(data),
        _from(from),
        _color(color){}
    bool operator() (const ChSquare &to) const
    {
        return _v->isMoveValid(_data, _from, to, _color);
    }

private:
    const ChValidator *_v;
    const ChBoardData *_data;
    ChSquare _from;
    ChPieceColor _color;
};

/*!
 * \brief Processes user clicks on board.
 *
 * Deselects \a selected square if it is clicked againe or if click is performed outside of possible
 * move squares.
 *
 * Selects new piece if \a index contains piece of the same color as Player.
 *
 * Performs move (emits moved() signal) if \a index is a possible move square.
 *
 * Updates selection information (emits selectionChanged() signal).
 *
 * \param index - clicked square.
 * \param selected - square with item to move or -1.
 * \param highlighted - list of possible target squares for move from \a selected square.
 */
void ChHumanPlayer::onSquareClicked(int index, int selected, const ChSquares &highlighted)
{
    if (!_inMove) {
        return;
    }
    // Selected item is clicked again. Unselect it
    if (index == selected) {
        emit selectionChanged(-1, ChSquares());
        return;
    }

    // Highlighted item is clicked. Make move
    if ((selected != -1) && (std::find(highlighted.begin(), highlighted.end(),
        ChSquare(index)) != highlighted.end())) {

        // make sure that it is possible move
        const ChPiece *piece = _data->at(ChSquare(selected));
        CH_SYSTEM_ASSERT(piece, tr("Square %1 should be not empty").arg(selected));
        ChSquares squares = piece->moves(ChSquare(selected), _data);
        bool contains = std::find(squares.begin(), squares.end(), ChSquare(index)) != squares.end();
        CH_SYSTEM_ASSERT(contains, tr("Cannot move from %1 to %2").arg(selected).arg(index));

        move(ChSquare(selected), ChSquare(index));
        return;
    }

    const ChPiece *piece = _data->at(ChSquare(index));
    if (!piece || (piece->color() != _color)) {
        // Clicked square does not contain item that may be set "selected"
        // Clear selection
        emit selectionChanged(-1, ChSquares());
        return;
    }
    else {
        // New item selected. Update selection and highlighting
        CH_SYSTEM_ASSERT(_validator, tr("Validator is not set"));
        ChSquares squares = piece->moves(ChSquare(index), _data);
        Ch_MoveChecker checker(_validator, _data, ChSquare(index), _color);
        squares.erase(std::remove_if(squares.begin(), squares.end(),
            std::not1(checker)), squares.end());
        emit selectionChanged(index, squares);
    }
}

void ChHumanPlayer::move(const ChSquare &from, const ChSquare &to)
{
    emit selectionChanged(-1, ChSquares());
    CH_SYSTEM_ASSERT(_validator, tr("Validator is not set"));
    // TODO: Human readable form of coordinate in message
    CH_SYSTEM_ASSERT(_validator->isMoveValid(_data, from, to, _color),
        tr("Impossible move is requested from %1 to %2 for player %3")
            .arg(from.index()).arg(to.index()).arg(_color));
    emit moved(from.index(), to.index());
}

