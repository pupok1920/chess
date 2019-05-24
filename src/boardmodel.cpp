#include <QtNetwork>

#include "boardmodel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent) {
      //_serverInfo.addr = QHostAddress("172.31.83.67");
      _serverInfo.addr = QHostAddress("0.0.0.0");
      _serverInfo.port = 8880;
      _undoStack = new QUndoStack(this);

      _receiverForUpdates = new QTcpServer(this);
      if(!_receiverForUpdates->listen(QHostAddress::AnyIPv4, 0)) {
        qDebug() << "Unable to start the receiver" << "\n";
        _receiverForUpdates->close();
        return;
      }
      connect(_receiverForUpdates, &QTcpServer::newConnection, this, &BoardModel::doUpdates);

      qDebug() << "_receiverForUpdates started and has addr:";
      qDebug() << _receiverForUpdates->serverAddress();
      qDebug() << _receiverForUpdates->serverPort() << "\n";
    }

BoardModel::~BoardModel() { }

int BoardModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return BOARD_SIZE * BOARD_SIZE;
}

QVariant BoardModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= BOARD_SIZE * BOARD_SIZE) {
        return QVariant();
    }

    Square square = static_cast<Square>(index.row());
    const Piece *piece = _data.at(square);

    switch (role) {
        case ItemTypeRole: {
            return piece ? piece->type() : "";
        }
        case ItemColorRole: {
            if(piece) {
                return (piece->color() == PieceColor::WHITE_COLOR) ? "white" : "black";
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

BoardModel::Color BoardModel::activePlayer() const {
    return _activePlayer;
}

BoardModel::Color BoardModel::playerColor() const {
    return _playerInfo.color == PieceColor::WHITE_COLOR ? Color::White : Color::Black;
}

void BoardModel::initialise() {
    if(doConnectionRqst()) {
      initialiseBoard(_data);
      _activePlayer = Color::White;
      emit playerColorChanged();
      emit activePlayerChanged();
      emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
    }
}

bool BoardModel::doConnectionRqst() {
    QTcpSocket *connectionRqst = new QTcpSocket(this);
    connect(connectionRqst, &QAbstractSocket::disconnected, connectionRqst, &QObject::deleteLater);

    connectionRqst->connectToHost(_serverInfo.addr, _serverInfo.port);
    if(connectionRqst->waitForConnected(5000)) {
        qDebug() << "connectionRqst connected to host: " << connectionRqst->peerAddress();
        qDebug() << "from host: " << connectionRqst->localAddress() << "\n";
    }
    else {
        qDebug() << "connection wasn't established";
        return false;
    }

    QJsonObject outJson;
    outJson["rqsttype"] = static_cast<double>(RqstType::CONNECTION);
    outJson["port"] = static_cast<double>(_receiverForUpdates->serverPort());

    QJsonDocument outDoc(outJson);
    connectionRqst->write(outDoc.toJson());
    connectionRqst->waitForBytesWritten();

    connectionRqst->waitForReadyRead(5000);

    QByteArray inData = connectionRqst->readAll();
    QJsonDocument inDoc(QJsonDocument::fromJson(inData));
    QJsonObject inJson(inDoc.object());
    qDebug() << "inData in doConnectionRqst(): " << inData;

    if(inJson.contains("answrtype") && inJson["answrtype"].isDouble()) {
      AnswrType type = static_cast<AnswrType>(inJson["answrtype"].toInt());
      switch(type) {
        case AnswrType::SUCCESS: {
          if(inJson.contains("playercolor") && inJson["playercolor"].isDouble()) {
            _playerInfo.color = static_cast<PieceColor>(inJson["playercolor"].toInt());
            connectionRqst->disconnectFromHost();
            qDebug() << "doConnectionRqst() was SUCCESS" << "\n";
            return true;
          }
        }
        case AnswrType::DENY: {
          connectionRqst->disconnectFromHost();
          qDebug() << "doConnectionRqst() was DENY" << "\n";
          return false;
        }
        default:
          return false;
      }
    }
    return false;
}

void BoardModel::doUpdates() {
    QTcpSocket *socket = _receiverForUpdates->nextPendingConnection();

    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    socket->waitForReadyRead(5000);

    QByteArray inData = socket->readAll();
    QJsonDocument inDoc(QJsonDocument::fromJson(inData));
    QJsonObject inJson(inDoc.object());

    socket->disconnectFromHost();
    qDebug() << "doUpdates() is called";

    if(inJson.contains("answrtype") && inJson["answrtype"].isDouble()) {
        if(!(inJson.contains("intfrom") && inJson["intfrom"].isDouble()))
            return;
        if(!(inJson.contains("intto") && inJson["intto"].isDouble()))
            return;

        int draggedFrom = inJson["intfrom"].toInt();
        int draggedTo = inJson["intto"].toInt();

        AnswrType type = static_cast<AnswrType>(inJson["answrtype"].toInt());
        switch(type) {
            case AnswrType::UPDATE: ordinaryMove(draggedFrom, draggedTo);
                                    break;
            case AnswrType::UPDATE_EN_PASSAN: if(inJson.contains("inttodelete") && inJson["inttodelete"].isDouble())
                                                  enPassantMove(draggedFrom, draggedTo, inJson["inttodelete"].toInt());
                                              break;
            default: break;
        }
    }
}

void BoardModel::move(int draggedFrom, int draggedTo) {
    qDebug() << "move() is called";

    qDebug() << "draggedFrom: " << draggedFrom;
    qDebug() << "draggedTo: " << draggedTo << "\n";

    QJsonObject outJson;
    outJson["rqsttype"] = static_cast<double>(RqstType::MOVE);
    outJson["intfrom"] = static_cast<double>(draggedFrom);
    outJson["intto"] = static_cast<double>(draggedTo);
    outJson["port"] = static_cast<double>(_receiverForUpdates->serverPort());

    checkMove(outJson);
}

void BoardModel::ordinaryMove(int intFrom, int intTo) {
    qDebug() << "ordinaryMove() is called" << "\n";
    Square squareFrom = static_cast<Square>(intFrom);
    Square squareTo = static_cast<Square>(intTo);
    changeModel(squareFrom, squareTo);
    _moves.append(qMakePair(intFrom, intTo));
}

void BoardModel::enPassantMove(int intFrom, int intTo, int intToDelete) {
    qDebug() << "enPassantMove() is called" << "\n";
    Square squareFrom = static_cast<Square>(intFrom);
    Square squareTo = static_cast<Square>(intTo);
    changeModel(squareFrom, squareTo);
    _moves.append(qMakePair(intFrom, intTo));
    Square squareToDelete = static_cast<Square>(intToDelete);
    changeModel(squareToDelete, Square(-1));
    _moves.append(qMakePair(intToDelete, -1));
}

PieceType BoardModel::getEnumPieceType(const QString &strType) {

      if(strType == "pawn") return PieceType::PAWN;

      if(strType == "rook") return PieceType::ROOK;

      if(strType == "knight") return PieceType::KNIGHT;

      if(strType == "bishop") return PieceType::BISHOP;

      if(strType == "queen") return PieceType::QUEEN;

      if(strType == "king") return PieceType::KING;
}

void BoardModel::checkMove(const QJsonObject &outJson) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    socket->connectToHost(_serverInfo.addr, _serverInfo.port);
    socket->waitForConnected(5000);

    QJsonDocument outDoc(outJson);
    socket->write(outDoc.toJson());
    socket->waitForBytesWritten(5000);

    socket->waitForReadyRead(5000);
    QByteArray inData = socket->readAll();
    QJsonDocument inDoc(QJsonDocument::fromJson(inData));
    QJsonObject inJson(inDoc.object());

    socket->disconnectFromHost();

    if(inJson.contains("answrtype") && inJson["answrtype"].isDouble()) {
        AnswrType type = static_cast<AnswrType>(inJson["answrtype"].toInt());
        switch(type) {
            case AnswrType::CORRECT: ordinaryMove(outJson["intfrom"].toInt(), outJson["intto"].toInt());
                                     break;
            case AnswrType::CORRECT_EN_PASSANT: enPassantMove(outJson["intfrom"].toInt(), outJson["intto"].toInt(), inJson["inttodelete"].toInt());
                                     break;
            default: break;
        }
    }
}

void BoardModel::changeModel(const Square &draggedFrom, const Square &draggedTo) {
    if(draggedTo.index() == -1) {
        _data.remove(draggedFrom);
        qDebug() << "squareToDelete is: " << draggedFrom.index() << "\n";
    }
    else {
        const Piece *cur = _data.at(draggedFrom);
        _data.remove(draggedTo);
        _data.remove(draggedFrom);
        _data.add(draggedTo, cur);
        if(_activePlayer == Color::Black) {
            _activePlayer = Color::White;
            emit activePlayerChanged();
        }
        else {
            _activePlayer = Color::Black;
            emit activePlayerChanged();
        }
    }

    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

bool BoardModel::isLoadedDataValid(const QVector<QPair<int, int> > &moves) {
    qDebug() << "dive into isDataValid()";
    initialiseBoard(_data);
    _activePlayer = Color::White;

    for(int i = 0; i < moves.size(); ++i) {

        int draggedFrom = moves[i].second;
        int draggedTo = moves[i].first;
        Square squareFrom = static_cast<Square>(draggedFrom);
        const Piece *pieceFrom = _data.at(squareFrom);
        qDebug() << draggedFrom;
        qDebug() << draggedTo;

        if(!pieceFrom) return false;

        if((_activePlayer == Color::White && pieceFrom->color() != PieceColor::WHITE_COLOR)
                || (_activePlayer == Color::Black && pieceFrom->color() != PieceColor::BLACK_COLOR)) return false;

        Square squareTo = static_cast<Square>(draggedTo);
        const Piece *pieceTo = _data.at(squareTo);

        if(pieceTo)
            if(pieceFrom->color() == pieceTo->color()) return false;

        const Piece *cur = _data.at(squareFrom);
        _data.remove(squareTo);
        _data.remove(squareFrom);
        _data.add(squareTo, cur);
        if(_activePlayer == Color::Black) {
            _activePlayer = Color::White;
        }
        else {
            _activePlayer = Color::Black;
        }
    }
    qDebug() << "isDataValid(): true" << "\n";
    return true;
}

void BoardModel::save(const QString &fileName) {
    bool res = FileHandler::save(fileName, _moves);
    if(!res)
        qDebug() << "couldn't save data to file";
}

void BoardModel::load(const QString &fileName) {
    if(!FileHandler::load(fileName, _moves))
        return;

    if(!isLoadedDataValid(_moves))
        return;

    initialiseBoard(_data);
    _activePlayer = Color::White;
    emit activePlayerChanged();
    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));

    _undoStack->clear();
    for(int i = 0; i < _moves.size(); ++i) {
        ReplayCommand *cmd = new ReplayCommand(&_data, _moves[i], 0);
        _undoStack->push(cmd);
    }
    _undoStack->setIndex(0);
}

void BoardModel::redo() {
    if(!_undoStack->canRedo())
        return;

    _undoStack->redo();


    if(_activePlayer == Color::Black) {
        _activePlayer = Color::White;
        emit activePlayerChanged();
    }
    else {
        _activePlayer = Color::Black;
        emit activePlayerChanged();
    }

    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
}

void BoardModel::undo() {
    if(!_undoStack->canUndo())
        return;

    _undoStack->undo();

    if(_activePlayer == Color::Black) {
        _activePlayer = Color::White;
        emit activePlayerChanged();
    }
    else {
        _activePlayer = Color::Black;
        emit activePlayerChanged();
    }

    emit dataChanged(index(0,0), index(BOARD_SIZE * BOARD_SIZE - 1, 0));
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

void BoardModel::initialiseBoard(BoardData &data) {
    data.clear();

    for(unsigned i = 0; i < BOARD_SIZE; ++i) {
        data.add(Square(6, i), data.pawn(PieceColor::WHITE_COLOR));
        data.add(Square(1, i), data.pawn(PieceColor::BLACK_COLOR));
    }

    data.add(Square(7, 0), data.rook(PieceColor::WHITE_COLOR));
    data.add(Square(7, 7), data.rook(PieceColor::WHITE_COLOR));

    data.add(Square(0, 0), data.rook(PieceColor::BLACK_COLOR));
    data.add(Square(0, 7), data.rook(PieceColor::BLACK_COLOR));

    data.add(Square(7, 1), data.knight(PieceColor::WHITE_COLOR));
    data.add(Square(7, 6), data.knight(PieceColor::WHITE_COLOR));

    data.add(Square(0, 1), data.knight(PieceColor::BLACK_COLOR));
    data.add(Square(0, 6), data.knight(PieceColor::BLACK_COLOR));

    data.add(Square(7, 2), data.bishop(PieceColor::WHITE_COLOR));
    data.add(Square(7, 5), data.bishop(PieceColor::WHITE_COLOR));

    data.add(Square(0, 2), data.bishop(PieceColor::BLACK_COLOR));
    data.add(Square(0, 5), data.bishop(PieceColor::BLACK_COLOR));

    data.add(Square(7, 3), data.queen(PieceColor::WHITE_COLOR));
    data.add(Square(0, 3), data.queen(PieceColor::BLACK_COLOR));

    data.add(Square(7, 4), data.king(PieceColor::WHITE_COLOR));
    data.add(Square(0, 4), data.king(PieceColor::BLACK_COLOR));
}
