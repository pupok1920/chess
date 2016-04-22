#include <itemmodel.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <functional>

int ItemModel::rowCount(const QModelIndex &parent) const {
    return itemList.count();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() > itemList.count())
        return QVariant();
    const Item &item = itemList[index.row()];
    if (role == source)
        return item.getsource();
    return QVariant();
}

void ItemModel::implemModel() {
    itemList[0].source = "src/rook_black.png";
    itemList[1].source = "src/knight_black.png";
    itemList[2].source = "src/bishop_black.png";
    itemList[3].source = "src/queen_black.png";
    itemList[4].source = "src/king_black.png";
    itemList[5].source = "src/bishop_black.png";
    itemList[6].source = "src/knight_black.png";
    itemList[7].source = "src/rook_black.png";
    for(i=8; i<16; i++)
        itemList[i].source = "src/pawn_black.png";
    for(i=16; i<48; i++)
        itemList[i].source = "";
    for(i=48; i<56; i++)
        itemList[i].source = "src/pawn_white.png";
    itemList[56].source = "src/rook_white.png";
    itemList[57].source = "src/knight_white.png";
    itemList[58].source = "src/bishop_white.png";
    itemList[59].source = "src/queen_white.png";
    itemList[60].source = "src/king_white.png";
    itemList[61].source = "src/bishop_white.png";
    itemList[62].source = "src/knight_white.png";
    itemList[63].source = "src/rook_white.png";
}
