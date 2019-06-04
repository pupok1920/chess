#include "replaycommand.h"

#include "boarddata.h"

ReplayCommand::ReplayCommand(BoardData *data, QPair<int, int> &move, QUndoCommand *parent)
    : QUndoCommand(parent),
      _data(data),
      _removedCur(nullptr) {
      _from = static_cast<Square>(move.second);
      _to = static_cast<Square>(move.first);
}

ReplayCommand::~ReplayCommand() {}

void ReplayCommand::redo() {
    // if enPassantMove happened
    if(_to.index() == -1) {
        _removedCur = _data->at(_from);
        _data->remove(_from);
    }
    // if ordinaryMove happened
    else {
        const Piece *cur = _data->at(_from);
        _removedCur = _data->at(_to);

        _data->remove(_to);
        _data->remove(_from);
        _data->add(_to, cur);
    }
}

void ReplayCommand::undo() {
    // if enPassantMove happened
    if(_to.index() == -1) {
        _data->add(_from, _removedCur);
        _removedCur = nullptr;
    }
    // if ordinaryMove happened
    else {
        const Piece *cur = _data->at(_to);

        _data->remove(_to);
        _data->add(_from, cur);
        _data->add(_to, _removedCur);
        _removedCur = nullptr;
    }
}