#include "chsquare.h"

#include "chexception.h"

/*! \class ChSquare
 * \brief Square coordinates on chess board.
 */

/*!
 * \brief Constructs square.
 * \param row - row of square on board (from 0 to \ref CH_BOARD_SIZE - 1)
 * \param column - column of square on board (from 0 to \ref CH_BOARD_SIZE - 1)
 * \exception ChLogicException in case if square is out of board.
 */
ChSquare::ChSquare(int row, int column):_index(row * CH_BOARD_SIZE + column)
{
    CH_LOGIC_ASSERT(
        (0 <= row) && (row < CH_BOARD_SIZE) &&
        (0 <= column) && (column < CH_BOARD_SIZE),
        tr("Incorrect square coordinate: %1:%2").arg(row).arg(column)
    );
}

/*!
 * \brief  Constructs square.
 * \param index - index on board. Squares on board are numbered from 0
 * till (\ref CH_BOARD_SIZE * CH_BOARD_SIZE - 1) from left to right from bottom to top.
 * \exception ChLogicException in case if square is out of board.
 */
ChSquare::ChSquare(int index):_index(index)
{
    CH_LOGIC_ASSERT(
        (0 <= index) && (index < CH_BOARD_SIZE * CH_BOARD_SIZE),
        tr("Incorrect square index: %1").arg(index)
    );
}

