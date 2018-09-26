#include "replaycommand.h"

#include "boarddata.h"

ReplayCommand::ReplayCommand(BoardData *data, QPair<int, int> &move, QUndoCommand *parent)
    : QUndoCommand(parent),
      _data(data),
      _from(Square(move.second)),
      _to(Square(move.first)),
      _removedCur(nullptr) {}

ReplayCommand::~ReplayCommand() {}

void ReplayCommand::redo() {
    const Piece *cur = _data->at(_from);
    _removedCur = _data->at(_to);

    _data->remove(_to);
    _data->remove(_from);
    _data->add(_to, cur);
}

void ReplayCommand::undo() {
    const Piece *cur = _data->at(_to);

    _data->remove(_to);
    _data->add(_from, cur);
    _data->add(_to, _removedCur);
    _removedCur = nullptr;
}
