#include "chboardmodel.h"

#include <QUndoStack>
#include <QFileInfo>

#include "chplayer.h"
#include "chvalidator.h"
#include "chmovecommand.h"
#include "chselection.h"
#include "chgameparser.h"
#include "chexception.h"

enum {
    /// Initial position of Rook
    CH_POS_ROOK = 0,
    /// Initial position of Knight
    CH_POS_KNIGHT = 1,
    /// Initial position of Bishop
    CH_POS_BISHOP = 2,
    /// Initial position of Queen
    CH_POS_QUEEN = 3,
    /// Initial position of King
    CH_POS_KING = 4
};

/*! \class ChBoardModel
 * \brief Communication point for QML.
 *
 * Data provider for QML. QML signals handler.
 *
 * Main workflow is shown on pictures below:
 *
 * \image html dfm.png.
 * \image html dfm1.png.
 */

ChBoardModel::ChBoardModel(QObject *parent)
    :QAbstractListModel(parent),
     _whitePlayer(0),
     _blackPlayer(0),
     _activePlayer(0),
     _validator(0),
     _undoStack(new QUndoStack(this)),
     _selection(new ChSelection())
{
    connect(_undoStack, SIGNAL(canRedoChanged(bool)), this, SIGNAL(canRedoChanged(bool)));
    connect(_undoStack, SIGNAL(canUndoChanged(bool)), this, SIGNAL(canUndoChanged(bool)));
}

ChBoardModel::~ChBoardModel()
{
}

/*!
 * \brief Number of rows in the model.
 *
 * Model is List (Qt QML limitation). So, each square is a row.
 * \return number of squares on the board.
 */
int ChBoardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return CH_BOARD_SIZE * CH_BOARD_SIZE;
}

QVariant ChBoardModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= CH_BOARD_SIZE * CH_BOARD_SIZE) {
        return QVariant();
    }
    const ChPiece *piece = _data.at(ChSquare(index.row()));
    switch (role) {
        case CellColorRole: {
            int row = index.row() / 8;
            int column = index.row() % 8;
            return ((row + column) % 2) ? "white" : "black";
        }
        case CellItemTypeRole: {
            return piece ? piece->type() : "";
        }
        case CellItemColorRole: {
            if (piece) {
                return (piece->color() == CH_WHITE_COLOR) ? "white" : "black";
            }
            else {
                return "";
            }
        }
        case CellItemSelectedRole: {
            return _selection->isSelected(ChSquare(index.row()));
        }
        case CellHighlightedRole: {
            return _selection->isHighlighted(ChSquare(index.row()));
        }
        case CellMoveIndicationRole: {
            // only King is indicated with "current move"
            if (piece && (piece->type() == _data.king(CH_BLACK_COLOR)->type())) {
                ChPieceColor c = piece->color();
                ChPieceColor pC = (_activePlayer == _whitePlayer) ? CH_WHITE_COLOR : CH_BLACK_COLOR;
                return (c == pC);
            }
            else {
                return false;
            }
        }
        default: {
            return QVariant();
        }
    }
}

void ChBoardModel::setPlayers(ChPlayer *white, ChPlayer *black)
{
    if (_whitePlayer) {
        _whitePlayer->disconnect();
    }
    if (_blackPlayer) {
        _blackPlayer->disconnect();
    }

    _whitePlayer = white;
    _blackPlayer = black;
    _activePlayer = _whitePlayer;

    // If both players are not a Human but automatic then
    // it is possible to recursively emit moved().
    // Use Qt::QueuedConnection to handle that case.
    connect(_whitePlayer, SIGNAL(moved(int, int)),
        this, SLOT(finishMove(int, int)), Qt::QueuedConnection);
    connect(_blackPlayer, SIGNAL(moved(int, int)),
        this, SLOT(finishMove(int, int)), Qt::QueuedConnection);
    connect(_whitePlayer, SIGNAL(selectionChanged(int, ChSquares)),
        this, SLOT(onSelectionChanged(int, ChSquares)));
    connect(_blackPlayer, SIGNAL(selectionChanged(int, ChSquares)),
        this, SLOT(onSelectionChanged(int, ChSquares)));

    _whitePlayer->setBoardData(&_data);
    _blackPlayer->setBoardData(&_data);
}

void ChBoardModel::setValidator(ChValidator *validator)
{
    _validator = validator;
}

/// Provides empty board.
void ChBoardModel::clear()
{
    _data.clear();
    _undoStack->clear();
    _activePlayer = 0;
    _whitePlayer->stopMove();
    _blackPlayer->stopMove();
    _selection->clearSelected();
    _selection->setHighlighted(ChSquares());
    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
}

/// Provides board with pieces in initial position.
void ChBoardModel::initialize()
{
    _undoStack->clear();
    _selection->clearSelected();
    _selection->setHighlighted(ChSquares());
    initializeData(_data);
    _activePlayer = _whitePlayer;
    _blackPlayer->stopMove();
    _activePlayer->startMove();
    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
}

struct Ch_DataLoader {
    Ch_DataLoader(ChBoardData *data, QUndoStack * undoStack):_data(data), _undoStack(undoStack)
    {
    }
    void operator()(const ChGameParser::Move &move)
    {
        ChMoveCommand *cmd = new ChMoveCommand(_data, move.first, move.second, 0);
        _undoStack->push(cmd);
    }

private:
    ChBoardData *_data;
    QUndoStack *_undoStack;
};

/*!
 * \brief Loads game for Replay mode.
 *
 * In case of error the signal alert() is emitted.
 *
 * \param fileName - game to load.
 * \return \a true if load is successful, \a false otherwise.
 */
bool ChBoardModel::load(const QString &fileName)
{
    bool result = true;
    try {
        loadImpl(fileName);
    }
    catch (ChLogicException &e) {
        qDebug("%s %d %s", qPrintable(e.description()), e.line(), qPrintable(e.file()));
        emit alert(tr("Cannot load game from '%1'. %2").arg(fileName).arg(e.description()));
        result = false;
    }

    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
    return result;
}

bool ChBoardModel::canUndo() const
{
    return _undoStack->canUndo();
}

bool ChBoardModel::canRedo() const
{
    return _undoStack->canRedo();
}

void ChBoardModel::onSquareClicked(int index)
{
    emit squareClicked(index,
        _selection->hasSelected() ? _selection->selected().index() : -1,
        _selection->highlighted()
    );
}

/*!
 * \brief Saves the game to \a fileName.
 *
 * In case of error the signal alert() is emitted.
 *
 * \param fileName - file to save the game.
 */
void ChBoardModel::save(const QString &fileName)
{
    try {

        ChGameParser parser;
        ChGameParser::Moves moves;
        for(int i = 0; i < _undoStack->count(); ++i) {
            const ChMoveCommand *cmd = dynamic_cast<const ChMoveCommand *>(_undoStack->command(i));
            CH_SYSTEM_ASSERT(cmd, tr("Bad command %1").arg(i));
            moves.push_back(std::make_pair(cmd->from().index(), cmd->to().index()));
        }
        QString fn = canonicalFormFileName(fileName);
        // Add ".xml" to files without suffix
        QFileInfo fi(fileName);
        if (fi.suffix().isEmpty()) {
            fn += ".xml";
        }
        parser.save(fn, moves);
    }
    catch (ChLogicException &e) {
        qDebug("%s %d %s", qPrintable(e.description()), e.line(), qPrintable(e.file()));
        emit alert(tr("Cannot save game to file '%1'. %2").arg(fileName).arg(e.description()));
    }
}

void ChBoardModel::finishMove(int from, int to)
{
    ChPieceColor color = (_activePlayer == _whitePlayer) ? CH_WHITE_COLOR : CH_BLACK_COLOR;
    if (_validator->isMoveValid(&_data, ChSquare(from), ChSquare(to), color)) {
        QUndoCommand *cmd = new ChMoveCommand(&_data, ChSquare(from), ChSquare(to), 0);
        _undoStack->push(cmd);
        _activePlayer->stopMove();
        _activePlayer = (_activePlayer == _whitePlayer) ? _blackPlayer : _whitePlayer;
        emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
        _activePlayer->startMove();
    }
    else {
        // if Player is a third-party component then it may produce incorrect
        // move. In that case incorrect move processing should be placed here.

        // In case of Human-Human game this is not possible.
        CH_THROW_SYSTEM_EX(tr("Incorrect move from %1 to %2").arg(from).arg(to));
    }
}

void ChBoardModel::onSelectionChanged(int selected, const ChSquares &highlighted)
{
    if (selected == -1) {
        _selection->clearSelected();
    }
    else {
        _selection->setSelected(ChSquare(selected));
    }
    _selection->setHighlighted(highlighted);
    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
}

void ChBoardModel::undo()
{
    // change active player to correctly highlight the player to perform next move.
    _activePlayer = (_undoStack->index() % 2) ? _whitePlayer : _blackPlayer;

    _undoStack->undo();
    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
}

void ChBoardModel::redo()
{
    // change active player to correctly highlight the player to perform next move.
    _activePlayer = (_undoStack->index() % 2) ? _whitePlayer : _blackPlayer;

    _undoStack->redo();
    emit dataChanged(index(0,0), index(CH_BOARD_SIZE * CH_BOARD_SIZE - 1, 0));
}

QHash<int, QByteArray> ChBoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CellColorRole] = "cell_color";
    roles[CellItemTypeRole] = "cell_item_type";
    roles[CellItemColorRole] = "cell_item_color";
    roles[CellItemSelectedRole] = "cell_item_selected";
    roles[CellHighlightedRole] = "cell_highlighted";
    roles[CellMoveIndicationRole] = "cell_move_indication";
    return roles;
}

void ChBoardModel::initializeData(ChBoardData &data)
{
    data.clear();

    const int LAST_ROW = CH_BOARD_SIZE - 1;
    const int LAST_COLUMN = CH_BOARD_SIZE - 1;
    // add pawns
    for (unsigned i = 0; i < CH_BOARD_SIZE; ++i) {
        data.add(ChSquare(1, i), data.pawn(CH_WHITE_COLOR));
        data.add(ChSquare(LAST_ROW - 1, i), data.pawn(CH_BLACK_COLOR));
    }

    // add kings
    data.add(ChSquare(0, CH_POS_KING), data.king(CH_WHITE_COLOR));
    data.add(ChSquare(LAST_ROW, CH_POS_KING), data.king(CH_BLACK_COLOR));

    // add queens
    data.add(ChSquare(0, CH_POS_QUEEN), data.queen(CH_WHITE_COLOR));
    data.add(ChSquare(LAST_ROW, CH_POS_QUEEN), data.queen(CH_BLACK_COLOR));

    // add rooks
    data.add(ChSquare(0, CH_POS_ROOK), data.rook(CH_WHITE_COLOR));
    data.add(ChSquare(0, LAST_COLUMN - CH_POS_ROOK), data.rook(CH_WHITE_COLOR));

    data.add(ChSquare(LAST_ROW, CH_POS_ROOK), data.rook(CH_BLACK_COLOR));
    data.add(ChSquare(LAST_ROW, LAST_COLUMN - CH_POS_ROOK), data.rook(CH_BLACK_COLOR));

    // add bishops
    data.add(ChSquare(0, CH_POS_BISHOP), data.bishop(CH_WHITE_COLOR));
    data.add(ChSquare(0, LAST_COLUMN - CH_POS_BISHOP), data.bishop(CH_WHITE_COLOR));

    data.add(ChSquare(LAST_ROW, CH_POS_BISHOP), data.bishop(CH_BLACK_COLOR));
    data.add(ChSquare(LAST_ROW, LAST_COLUMN - CH_POS_BISHOP), data.bishop(CH_BLACK_COLOR));

    // add knights
    data.add(ChSquare(0, CH_POS_KNIGHT), data.knight(CH_WHITE_COLOR));
    data.add(ChSquare(0, LAST_COLUMN - CH_POS_KNIGHT), data.knight(CH_WHITE_COLOR));

    data.add(ChSquare(LAST_ROW, CH_POS_KNIGHT), data.knight(CH_BLACK_COLOR));
    data.add(ChSquare(LAST_ROW, LAST_COLUMN - CH_POS_KNIGHT), data.knight(CH_BLACK_COLOR));

}

QString ChBoardModel::canonicalFormFileName(const QString &fileName) const
{
    QString fn = fileName;
    fn.replace("file://", "");
#ifdef Q_OS_WIN
    if (fn.startsWith('/')) {
        fn = fn.mid(1);
    }
#endif
    return fn;
}

void ChBoardModel::loadImpl(const QString &fileName)
{
    // Load file. Process may throw exceptions.
    QString fn = canonicalFormFileName(fileName);
    ChGameParser parser;
    ChGameParser::Moves moves = parser.load(fn);

    // Create test board and command stack
    ChBoardData d;
    QUndoStack s;
    initializeData(d);
    std::for_each(moves.begin(), moves.end(), Ch_DataLoader(&d, &s));

    // If nothing happens in test board then load game for re-play
    // Now we do not expect any exception
    try {
        _undoStack->clear();
        _selection->clearSelected();
        _selection->setHighlighted(ChSquares());
        initializeData(_data);
        std::for_each(moves.begin(), moves.end(), Ch_DataLoader(&_data, _undoStack));
        _activePlayer = _whitePlayer;
        _blackPlayer->stopMove();
        _whitePlayer->stopMove();
        _undoStack->setIndex(0);
    }
    catch (ChLogicException &e) {
        // this should never happens. Indicates internal system error
        CH_THROW_SYSTEM_EX(tr("%1 (original file %2, line %3)")
            .arg(e.description()).arg(e.file()).arg(e.line()));
    }
}

