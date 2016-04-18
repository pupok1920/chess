#include "chselection.h"

#include "chsquare.h"
#include "chexception.h"

/*! \class ChSelection
 * \brief Handles selection of squares on the board.
 *
 * \b Selected square is the square clicked by the user to move piece from it.
 *
 * \b Highlighted squares are the possible target squares to move the selected piece.
 *
*/
ChSelection::ChSelection():_hasSelected(false)
{

}

ChSelection::~ChSelection()
{

}

bool ChSelection::isSelected(const ChSquare &square) const
{
    return (_hasSelected && (_selected == square));
}

void ChSelection::setSelected(const ChSquare &square)
{
    _hasSelected = true;
    _selected = square;
}

bool ChSelection::hasSelected() const
{
    return _hasSelected;
}

void ChSelection::clearSelected()
{
    _hasSelected = false;
}

const ChSquare &ChSelection::selected() const
{
    CH_SYSTEM_ASSERT(_hasSelected, tr("No selected item"));
    return _selected;
}

bool ChSelection::isHighlighted(const ChSquare &square) const
{
    return std::find(_highlighted.begin(), _highlighted.end(), square) != _highlighted.end();
}

void ChSelection::setHighlighted(const ChSquares &squares)
{
    _highlighted = squares;
}

const ChSquares &ChSelection::highlighted() const
{
    return _highlighted;
}
