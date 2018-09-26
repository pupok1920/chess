#ifndef __REPLAYCOMMANDBVDSVJKSBVVBVDIHVUISHVSBB__
#define __REPLAYCOMMANDBVDSVJKSBVVBVDIHVUISHVSBB__
#include <QUndoCommand>
#include <QPair>
#include "square.h"

class BoardData;
class Piece;

class ReplayCommand: public QUndoCommand {

public:
    ReplayCommand(BoardData *data, QPair<int, int> &move, QUndoCommand *parent);
    ~ReplayCommand();

    void redo();
    void undo();

private:
    Q_DISABLE_COPY(ReplayCommand)
    BoardData *_data;
    Square _from;
    Square _to;
    const Piece *_removedCur;
};

#endif // __REPLAYCOMMANDBVDSVJKSBVVBVDIHVUISHVSBB__

