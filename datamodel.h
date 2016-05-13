#ifndef ITEMMODEL
#define ITEMMODEL
#include <QAbstractListModel>

#endif // ITEMMODEL

class ItemModel: public QAbstractListModel
{
  Q_OBJECT

public:
    ItemModel(QObject *parent = 0);

    /*int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;*/

private:
    QList<item> itemList;

public:
    int source = Qt::UserRole + 1;

    ItemModel::ItemModel(QObject *parent)
        : QAbstractListModel(parent) {
            QHash<int, QByteArray> roles;
            roles[source] = "source";
            setRoleNames(roles);
    }
}
