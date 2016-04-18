#ifndef CHMOVECOMMAND_H
#define CHMOVECOMMAND_H

#include <QUndoCommand>

#include "chlib.h"
#include "chsquare.h"

class ChBoardData;
class ChPiece;

class QMLCHESSLIB_COMMON_DLLSPEC ChMoveCommand : public QUndoCommand
{
    Q_DECLARE_TR_FUNCTIONS(ChMoveCommand)
public:
    ChMoveCommand(ChBoardData *data, const ChSquare &from, const ChSquare &to,
        QUndoCommand *parent);
    ~ChMoveCommand();

    void redo();
    void undo();

    ChSquare from() const;
    ChSquare to() const;

private:
    Q_DISABLE_COPY(ChMoveCommand)
    ChBoardData *_data;
    ChSquare _from;
    ChSquare _to;
    const ChPiece *_removedPiece;

};

#endif // CHMOVECOMMAND_H
