#include "boardmodel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent) {
    connect(this, SIGNAL(activePlayerChanged()),
            this, SLOT(getActivePlayer()));
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

bool BoardModel::getActivePlayer() const {
    if(_activePlayer == WHITE_COLOR) {
        return false;
    }
    else {
        return true;
    }
}

void BoardModel::initialize() {
    initializeData(_data);
    _activePlayer = WHITE_COLOR;
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

void BoardModel::finishMove(int draggedFrom, int draggedTo) {
    int oldX = draggedFrom % BOARD_SIZE;
    int oldY = draggedFrom / BOARD_SIZE;
    int newX = draggedTo % BOARD_SIZE;
    int newY = draggedTo / BOARD_SIZE;

    const Piece *pieceFrom = _data.at(Square(draggedFrom));
    const Piece *pieceTo = _data.at(Square(draggedTo));
    //bool result = pieceFrom->moves(oldX, oldY, newX, newY);

    if(pieceFrom != 0) {
        bool result = pieceFrom->moves(oldX, oldY, newX, newY);
        changeModel(result, Square(draggedFrom), Square(draggedTo));
    }
        //return;


    /*if(pieceFrom->color() != pieceTo->color()) {
        //bool result = pieceFrom->moves(oldX, oldY, newX, newY);
    }
    else {
        emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    }*/

    //_activePlayer = (WHITE_COLOR) ? BLACK_COLOR : WHITE_COLOR;

}

void BoardModel::changeModel(bool result, Square draggedFrom, Square draggedTo) {
    const Piece *cur = _data.at(draggedFrom);
    if(result) {
        _data.remove(draggedTo);
        _data.remove(draggedFrom);
        _data.add(draggedTo, cur);
        _activePlayer = (WHITE_COLOR) ? BLACK_COLOR : WHITE_COLOR;
        //emit activePlayerChanged();
        emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    }
}

QHash<int, QByteArray> BoardModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[ItemTypeRole] = "item_type";
    roles[ItemColorRole] = "item_color";
    return roles;
}

void BoardModel::initializeData(BoardData &data) {
    for(unsigned i = 0; i < BOARD_SIZE; ++i) {
        data.add(Square(1, i), data.pawn(WHITE_COLOR));
        data.add(Square(6, i), data.pawn(BLACK_COLOR));
    }

    data.add(Square(0, 0), data.rook(WHITE_COLOR));
    data.add(Square(0, 7), data.rook(WHITE_COLOR));

    data.add(Square(7, 0), data.rook(BLACK_COLOR));
    data.add(Square(7, 7), data.rook(BLACK_COLOR));

    data.add(Square(0, 1), data.knight(WHITE_COLOR));
    data.add(Square(0, 6), data.knight(WHITE_COLOR));

    data.add(Square(7, 1), data.knight(BLACK_COLOR));
    data.add(Square(7, 6), data.knight(BLACK_COLOR));

    data.add(Square(0, 2), data.bishop(WHITE_COLOR));
    data.add(Square(0, 5), data.bishop(WHITE_COLOR));

    data.add(Square(7, 2), data.bishop(BLACK_COLOR));
    data.add(Square(7, 5), data.bishop(BLACK_COLOR));

    data.add(Square(0, 3), data.queen(WHITE_COLOR));
    data.add(Square(7, 3), data.queen(BLACK_COLOR));

    data.add(Square(0, 4), data.king(WHITE_COLOR));
    data.add(Square(7, 4), data.king(BLACK_COLOR));

}
