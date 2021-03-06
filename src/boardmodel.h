#ifndef __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#include <QAbstractListModel>
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QErrorMessage>
#include <QTextStream>
#include <QPair>
#include <QVector>
#include <QDebug>
#include <utility>
#include "boarddata.h"
#include "replaycommand.h"

class QUndoStack;

class BoardModel: public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        ItemTypeRole = Qt::UserRole + 1,
        ItemColorRole
    };

    Q_PROPERTY(bool activePlayer READ activePlayer NOTIFY activePlayerChanged)

public:
    explicit BoardModel(QObject *parent = nullptr);
    ~BoardModel();

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool activePlayer() const;

    Q_INVOKABLE void initialise();
    Q_INVOKABLE void move(int draggedFrom, int draggedTo);
    Q_INVOKABLE void save(const QString  &fileName);
    Q_INVOKABLE void load(const QString  &fileName);
    Q_INVOKABLE void redo();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void clear();

    BoardModel& operator=(BoardModel const&) = delete;
    BoardModel(BoardModel const&) = delete;

signals:
    void activePlayerChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
    QString cutFileName(const QString &fileName) const;
    void changeModel(bool result, Square draggedFrom, Square draggedTo);
    bool isFileValid(QFile &file);
    bool isDataValid(QTextStream &in);

private:
    void initialiseData(BoardData &data);

private:
    QVector<QPair<int, int> > _moves;
    BoardData _data;
    QUndoStack *_undoStack;

    bool  _activePlayer;
};

#endif // __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
