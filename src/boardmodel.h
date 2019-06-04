#ifndef __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#include <QAbstractListModel>
#include <QDebug>
#include <utility>

#include "boarddata.h"
#include "structs.h"
#include "replaycommand.h"
#include "filehandler.h"

class QUndoStack;
class QTcpServer;

class BoardModel: public QAbstractListModel {
    Q_OBJECT

    enum Roles {
        ItemTypeRole = Qt::UserRole + 1,
        ItemColorRole
    };

    Q_PROPERTY(Color activePlayer READ activePlayer NOTIFY activePlayerChanged)
    Q_PROPERTY(Color playerColor READ playerColor NOTIFY playerColorChanged)

public:
    explicit BoardModel(QObject *parent = nullptr);
    ~BoardModel();

    enum class Color {
      White,
      Black
    };
    Q_ENUM(Color)

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Color activePlayer() const;
    Color playerColor() const;

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
    void playerColorChanged();

private:
    QHash<int, QByteArray> roleNames() const;

    bool isLoadedDataValid(const QVector<QPair<int, int>> &moves);

    void initialiseBoard(BoardData &data);
    bool doConnectionRqst();
    void doUpdates();
    void checkMove(const QJsonObject &outJson);
    void ordinaryMove(int draggedFrom, int draggedTo);
    void enPassantMove(int draggedFrom, int draggedTo, int intToDelete);
    PieceType getEnumPieceType(const QString &strType);
    void changeModel(const Square &draggedFrom, const Square &draggedTo);

private:
    QVector<QPair<int, int>> _moves;
    BoardData _data;
    Color  _activePlayer = Color::White;
    Player _playerInfo;
    ServerInfo _serverInfo;
    QUndoStack *_undoStack = nullptr;
    QTcpServer *_receiverForUpdates = nullptr;
};
#endif // __BOARDMODELNJNBDJBNDLBNDLBNDKBNDKBNDKL__
