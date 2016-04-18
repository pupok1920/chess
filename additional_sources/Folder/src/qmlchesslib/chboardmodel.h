#ifndef CHBOARDMODEL_H
#define CHBOARDMODEL_H

#include <memory>

#include <QAbstractListModel>

#include "chlib.h"
#include "chconsts.h"
#include "chboarddata.h"

class QUndoStack;
class ChPlayer;
class ChValidator;
class ChSelection;

class QMLCHESSLIB_COMMON_DLLSPEC ChBoardModel : public QAbstractListModel
{
    Q_OBJECT

    enum ChRoles {
        CellColorRole = Qt::UserRole + 1,
        CellItemTypeRole,
        CellItemColorRole,
        CellItemSelectedRole,
        CellHighlightedRole,
        CellMoveIndicationRole
    };

public:
    explicit ChBoardModel(QObject *parent = 0);
    ~ChBoardModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setPlayers(ChPlayer *white, ChPlayer *black);
    void setValidator(ChValidator *validator);

    Q_INVOKABLE bool load(const QString &fileName);
    Q_INVOKABLE bool canUndo() const;
    Q_INVOKABLE bool canRedo() const;

signals:
    void squareClicked(int index, int selected, const ChSquares &highlighted);
    void canRedoChanged(bool canRedo);
    void canUndoChanged(bool canUndo);
    void alert(const QString& description);

public slots:
    void clear();
    void initialize();
    void onSquareClicked(int index);
    void save(const QString &fileName);

    void finishMove(int from, int to);
    void onSelectionChanged(int selected, const ChSquares &highlighted);
    void undo();
    void redo();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    void initializeData(ChBoardData &data);
    QString canonicalFormFileName(const QString &fileName) const;
    void loadImpl(const QString &fileName);
private:
    Q_DISABLE_COPY(ChBoardModel)
    ChBoardData _data;
    ChPlayer *_whitePlayer;
    ChPlayer *_blackPlayer;
    ChPlayer *_activePlayer;
    ChValidator *_validator;
    QUndoStack *_undoStack;
    // C++11 is not used in the project, so auto_ptr is applied instead of
    // unique_ptr
    std::auto_ptr<ChSelection> _selection;
};

#endif // CHBOARDMODEL_H
