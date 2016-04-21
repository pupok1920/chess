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
    if (role == SourceRole)
        return item.getSource();
    return QVariant();
}

void ItemModel::implemModel() {

}
