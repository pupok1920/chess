#ifndef __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include <QVector>
#include <QDebug>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>
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


    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool activePlayer() const;

    Q_INVOKABLE void initialise();

    Q_INVOKABLE void move(int draggedFrom, int draggedTo);
    Q_INVOKABLE void save(const QString  &fileName);

signals:
    void activePlayerChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
    QString cutFileName(const QString &fileName) const;
    void changeModel(bool result, Square draggedFrom, Square draggedTo);

private:
    void initialiseData(BoardData &data);

private:
    //typedef std::pair<QByteArray, QByteArray> Move;
    //typedef std::vector<Move> Moves;
    //typedef std::vector<QString> StringMoves;
    //QPair<QByteArray, QByteArray> _move;
    QVector<QPair<int, int> > _moves;
    //*//////QList<int> _moves;
    //Moves _moves;
    /*StringMoves _stringMoves;
    typedef std::vector<int> Move;
    Move _move;*/

    BoardData _data;
    bool  _activePlayer;
};

#endif // __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
