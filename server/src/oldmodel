#include "boardmodel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent) {
}

BoardModel::~BoardModel(){}

int BoardModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return BOARD_SIZE * BOARD_SIZE;
}

QVariant BoardModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= BOARD_SIZE * BOARD_SIZE) {
        return QVariant();
    }
    const Piece *piece = _data.at(Square(index.row()));
    switch (role) {
        case ItemTypeRole: {
            return piece ? piece->type() : "";
        }
        case ItemColorRole: {
            if(piece) {
                return (piece->color() == WHITE_COLOR) ? "white" : "black";
            }
            else {
                return "";
            }
        }
        default: {
            return QVariant();
        }
    }
}

bool BoardModel::activePlayer() const {
    return _activePlayer;
}

void BoardModel::initialise() {
    initialiseData(_data);
    _activePlayer = true;
    emit activePlayerChanged();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

void BoardModel::move(int draggedFrom, int draggedTo) {

    const Piece *pieceFrom = _data.at(Square(draggedFrom));
    
    if(pieceFrom == 0) return; 
    
    if((_activePlayer == true && pieceFrom->color() != WHITE_COLOR)
            || (_activePlayer == false && pieceFrom->color() != BLACK_COLOR)) return;
    
    const Piece *pieceTo = _data.at(Square(draggedTo));

    if(pieceTo == 0 || pieceFrom->color() != pieceTo->color()) {
	int oldX = draggedFrom % BOARD_SIZE;
	int oldY = draggedFrom / BOARD_SIZE;
	int newX = draggedTo % BOARD_SIZE;
	int newY = draggedTo / BOARD_SIZE;

	bool result = pieceFrom->isMoveValid(oldX, oldY, newX, newY);
    changeModel(result, Square(draggedFrom), Square(draggedTo));
    _moves.append(qMakePair(draggedFrom, draggedTo));
    }    
}

void BoardModel::changeModel(bool result, Square draggedFrom, Square draggedTo) {
    const Piece *cur = _data.at(draggedFrom);
    if(result) {
        _data.remove(draggedTo);
        _data.remove(draggedFrom);
        _data.add(draggedTo, cur);

        if(_activePlayer == false) {
            _activePlayer = true;
            emit activePlayerChanged();
        }
        else {
            _activePlayer = false;
            emit activePlayerChanged();
        }
        
        emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    }
}

void BoardModel::save(const QString &fileName) {
    QString fn = cutFileName(fileName);
    QFile file(fn);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    for(int i = 0; i < _moves.size(); ++i) {
        out << _moves[i].first << "\n";
        out << _moves[i].second << "\n";
    }
    file.close();
    //qDebug() << _moves;
}

void BoardModel::load(const QString &fileName) {
    QString fn = cutFileName(fileName);
    QFile file(fn);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    _moves.clear();
    _movesIter = 0;
    initialiseData(_data);
    QTextStream in(&file);
    while(!in.atEnd()) {
        _moves.append(qMakePair(in.readLine().toInt(), in.readLine().toInt()));
    }
    file.close();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    //qDebug() << _moves;
}

void BoardModel::redo() {
    if(_movesIter >= _moves.size()) {
        return;
    }
    Square from = Square(_moves[_movesIter].second);
    Square to = Square(_moves[_movesIter].first);
    const Piece *cur = _data.at(from);
    const Piece *removedCur = _data.at(to);
    _removedPieces.add(Square(_movesIter), removedCur);

    _data.remove(to);
    _data.remove(from);
    _data.add(to, cur);

    if(_activePlayer == false) {
        _activePlayer = true;
        emit activePlayerChanged();
    }
    else {
        _activePlayer = false;
        emit activePlayerChanged();
    }

    ++_movesIter;
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    //qDebug() << _movesIter;

}

void BoardModel::undo() {
    if(_movesIter == 0) {
        return;
    }
    else {
        Square from = Square(_moves[_movesIter - 1].second);
        Square to = Square(_moves[_movesIter - 1].first);
        const Piece *cur = _data.at(to);

        _data.remove(to);
        _data.add(from, cur);
        _data.add(to, _removedPieces.at(Square(_movesIter - 1)));

        if(_activePlayer == false) {
            _activePlayer = true;
            emit activePlayerChanged();
        }
        else {
            _activePlayer = false;
            emit activePlayerChanged();
        }

        --_movesIter;
        emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
        //qDebug() << _movesIter;
    }
}

void BoardModel::clear() {
    _data.clear();
    _removedPieces.clear();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

QHash<int, QByteArray> BoardModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[ItemTypeRole] = "item_type";
    roles[ItemColorRole] = "item_color";
    return roles;
}

QString BoardModel::cutFileName(const QString &fileName) const
{
    QString fn = fileName;
    fn.replace("file://", "");
    return fn;
}

void BoardModel::initialiseData(BoardData &data) {
    for(unsigned i = 0; i < BOARD_SIZE; ++i) {
        data.add(Square(6, i), data.pawn(WHITE_COLOR));
        data.add(Square(1, i), data.pawn(BLACK_COLOR));
    }

    data.add(Square(7, 0), data.rook(WHITE_COLOR));
    data.add(Square(7, 7), data.rook(WHITE_COLOR));

    data.add(Square(0, 0), data.rook(BLACK_COLOR));
    data.add(Square(0, 7), data.rook(BLACK_COLOR));

    data.add(Square(7, 1), data.knight(WHITE_COLOR));
    data.add(Square(7, 6), data.knight(WHITE_COLOR));

    data.add(Square(0, 1), data.knight(BLACK_COLOR));
    data.add(Square(0, 6), data.knight(BLACK_COLOR));

    data.add(Square(7, 2), data.bishop(WHITE_COLOR));
    data.add(Square(7, 5), data.bishop(WHITE_COLOR));

    data.add(Square(0, 2), data.bishop(BLACK_COLOR));
    data.add(Square(0, 5), data.bishop(BLACK_COLOR));

    data.add(Square(7, 3), data.queen(WHITE_COLOR));
    data.add(Square(0, 3), data.queen(BLACK_COLOR));

    data.add(Square(7, 4), data.king(WHITE_COLOR));
    data.add(Square(0, 4), data.king(BLACK_COLOR));

}
