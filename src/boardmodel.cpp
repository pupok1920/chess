#include "boardmodel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent) {}

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

void BoardModel::initialize() {
    initializeData(_data);
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
