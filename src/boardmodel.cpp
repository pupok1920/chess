#include "boardmodel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent),
      _undoStack(new QUndoStack(this)),
      _activePlayer(true) { }

BoardModel::~BoardModel() { }

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

bool BoardModel::activePlayer() const {
    return _activePlayer;
}

void BoardModel::initialise() {
    initialiseData(_data);
    _activePlayer = true;
    //QErrorMessage *errorMessage = new QErrorMessage();
    //errorMessage->showMessage("done");
    emit activePlayerChanged();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

void BoardModel::move(int draggedFrom, int draggedTo) {

    const Piece *pieceFrom = _data.at(Square(draggedFrom));
    
    if(pieceFrom == 0) return; 
    
    if((_activePlayer == true && pieceFrom->color() != WHITE_COLOR)
            || (_activePlayer == false && pieceFrom->color() != BLACK_COLOR)) return;
    
    const Piece *pieceTo = _data.at(Square(draggedTo));

    if(pieceTo == 0 || pieceFrom->color() != pieceTo->color()) {
        int oldX = draggedFrom % BOARD_SIZE;
        int oldY = draggedFrom / BOARD_SIZE;
        int newX = draggedTo % BOARD_SIZE;
        int newY = draggedTo / BOARD_SIZE;

        bool result = pieceFrom->isMoveValid(oldX, oldY, newX, newY);
        changeModel(result, Square(draggedFrom), Square(draggedTo));
        _moves.append(qMakePair(draggedFrom, draggedTo));
    }    
}

void BoardModel::changeModel(bool result, Square draggedFrom, Square draggedTo) {
    const Piece *cur = _data.at(draggedFrom);
    if(result) {
        _data.remove(draggedTo);
        _data.remove(draggedFrom);
        _data.add(draggedTo, cur);

        if(_activePlayer == false) {
            _activePlayer = true;
            emit activePlayerChanged();
        }
        else {
            _activePlayer = false;
            emit activePlayerChanged();
        }
        
        emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    }
}

bool BoardModel::isFileValid(QFile &file) {

    bool result = true;
    QErrorMessage *errorMessage = new QErrorMessage();

    if(file.exists() == false) {
        errorMessage->showMessage("The file doesn't exist.", "ErrorMessage");
        return result = false;
    }

    QFileInfo fi = file.fileName();
    if(fi.suffix() != "txt") {
        errorMessage->showMessage("The type of the file isn't '.txt'", "ErrorMessage");
         return result = false;
    }

    enum QFileDevice::FileError fault = file.error();
    switch(fault) {
        case 1: {
            errorMessage->showMessage("An error occurred when reading from the file.", "ErrorMessage");
            return result = false;
        }
        case 3: {
            errorMessage->showMessage("A fatal error occurred.", "ErrorMessage");
            return result = false;
        }
        case 4: {
            errorMessage->showMessage("Out of resources (e.g., too many open files, out of memory, etc.)", "ErrorMessage");
            return result = false;
        }
        case 5: {
            errorMessage->showMessage("The file could not be opened.", "ErrorMessage");
            return result = false;
        }
        case 6: {
            errorMessage->showMessage("The operation was aborted.", "ErrorMessage");
            return result = false;
        }
        case 7: {
            errorMessage->showMessage("A timeout occurred.", "ErrorMessage");
            return result = false;
        }
        case 8: {
            errorMessage->showMessage("An unspecified error occurred.", "ErrorMessage");
            return result = false;
        }
    }

    QTextStream in(&file);
    if(in.readLine().toInt() == 0) {
        errorMessage->showMessage("Wrong file. Try to use another one.", "ErrorMessage");
        return result = false;
    }
    in.seek(0);

    unsigned int sum = 0;
    while(!in.atEnd()) {
        if(in.readLine().toInt() > 63) {
            errorMessage->showMessage("Bad file. Try to use another one.", "ErrorMessage");
            return result = false;
        }
        ++sum;
    }
    in.seek(0);

    if(sum % 2) {
        errorMessage->showMessage("Something wrong with that file. Try to use another one.", "ErrorMessage");
        return result = false;
    }

    bool testData = isDataValid(in);
    if(!testData) {
        errorMessage->showMessage("The file contains incorrect data. Try to use another one.", "ErrorMessage");
        return result = false;
    }
    file.seek(0);

    return result;
}

bool BoardModel::isDataValid(QTextStream &in) {
    initialiseData(_data);
    _activePlayer = true;

    while(!in.atEnd()) {
        int draggedFrom = in.readLine().toInt();
        int draggedTo = in.readLine().toInt();
        const Piece *pieceFrom = _data.at(Square(draggedFrom));

        if(pieceFrom == 0) return false;

        if((_activePlayer == true && pieceFrom->color() != WHITE_COLOR)
                || (_activePlayer == false && pieceFrom->color() != BLACK_COLOR)) return false;

        const Piece *pieceTo = _data.at(Square(draggedTo));

        if(pieceTo == 0 || pieceFrom->color() != pieceTo->color()) {
            int oldX = draggedFrom % BOARD_SIZE;
            int oldY = draggedFrom / BOARD_SIZE;
            int newX = draggedTo % BOARD_SIZE;
            int newY = draggedTo / BOARD_SIZE;

            bool result = pieceFrom->isMoveValid(oldX, oldY, newX, newY);
            const Piece *cur = _data.at(Square(draggedFrom));
            if(result) {
                _data.remove(Square(draggedTo));
                _data.remove(Square(draggedFrom));
                _data.add(Square(draggedTo), cur);
                if(_activePlayer == false) {
                    _activePlayer = true;
                }
                else {
                    _activePlayer = false;
                }
            }
            else {
                return false;
            }
        }
    }
    return true;
}

void BoardModel::save(const QString &fileName) {
    QString fn = cutFileName(fileName);
    QFile file(fn);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    for(int i = 0; i < _moves.size(); ++i) {
        out << _moves[i].first << "\n";
        out << _moves[i].second << "\n";
    }
    file.close();
    //qDebug() << _moves;
}

void BoardModel::load(const QString &fileName) {
    QString fn = cutFileName(fileName);
    QFile file(fn);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    bool trueFile = isFileValid(file);
    if(!trueFile) {
        return;
    }

    clear();
    initialise();
    QTextStream in(&file);
    while(!in.atEnd()) {
        _moves.append(qMakePair(in.readLine().toInt(), in.readLine().toInt()));
    }
    file.close();

    for(unsigned i = 0; i < _moves.size(); ++i) {
        ReplayCommand *cmd = new ReplayCommand(&_data, _moves[i], 0);
        _undoStack->push(cmd);
    }
    _undoStack->setIndex(0);
}

void BoardModel::redo() {

    if(!_undoStack->canRedo())
        return;

    _undoStack->redo();


    if(_activePlayer == false) {
        _activePlayer = true;
        emit activePlayerChanged();
    }
    else {
        _activePlayer = false;
        emit activePlayerChanged();
    }

    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    //qDebug() << _movesIter;

}

void BoardModel::undo() {

    if(!_undoStack->canUndo())
        return;

    _undoStack->undo();

    if(_activePlayer == false) {
        _activePlayer = true;
        emit activePlayerChanged();
    }
    else {
        _activePlayer = false;
        emit activePlayerChanged();
    }

    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    //qDebug() << _movesIter;
}

void BoardModel::clear() {
    _data.clear();
    _moves.clear();
    _undoStack->clear();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

QHash<int, QByteArray> BoardModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[ItemTypeRole] = "item_type";
    roles[ItemColorRole] = "item_color";
    return roles;
}

QString BoardModel::cutFileName(const QString &fileName) const
{
    QString fn = fileName;
    fn.replace("file://", "");
    return fn;
}

void BoardModel::initialiseData(BoardData &data) {    

    data.clear();

    for(unsigned i = 0; i < BOARD_SIZE; ++i) {
        data.add(Square(6, i), data.pawn(WHITE_COLOR));
        data.add(Square(1, i), data.pawn(BLACK_COLOR));
    }

    data.add(Square(7, 0), data.rook(WHITE_COLOR));
    data.add(Square(7, 7), data.rook(WHITE_COLOR));

    data.add(Square(0, 0), data.rook(BLACK_COLOR));
    data.add(Square(0, 7), data.rook(BLACK_COLOR));

    data.add(Square(7, 1), data.knight(WHITE_COLOR));
    data.add(Square(7, 6), data.knight(WHITE_COLOR));

    data.add(Square(0, 1), data.knight(BLACK_COLOR));
    data.add(Square(0, 6), data.knight(BLACK_COLOR));

    data.add(Square(7, 2), data.bishop(WHITE_COLOR));
    data.add(Square(7, 5), data.bishop(WHITE_COLOR));

    data.add(Square(0, 2), data.bishop(BLACK_COLOR));
    data.add(Square(0, 5), data.bishop(BLACK_COLOR));

    data.add(Square(7, 3), data.queen(WHITE_COLOR));
    data.add(Square(0, 3), data.queen(BLACK_COLOR));

    data.add(Square(7, 4), data.king(WHITE_COLOR));
    data.add(Square(0, 4), data.king(BLACK_COLOR));

}
