#ifndef BOARDMODEL
#define BOARDMODEL
#include <QAbstractListModel>
#include "boarddata.h"

class BoardModel: public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        ItemTypeRole = Qt::UserRole + 1,
        ItemColorRole
    };

    Q_PROPERTY(bool activePlayer READ activePlayer NOTIFY activePlayerChanged)

public:
    explicit BoardModel(QObject *parent = 0);
    ~BoardModel();


    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool activePlayer() const;

    void initialize();

    Q_INVOKABLE void finishMove(int draggedFrom, int draggedTo);

signals:
    void activePlayerChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

    void changeModel(bool result, Square draggedFrom, Square draggedTo);

private:
    void initializeData(BoardData &data);

private:
    BoardData _data;
    bool  _activePlayer;
};

#endif // BOARDMODEL

