#include <QtNetwork>
#include <QtCore>
#include <QByteArray>
#include <QDebug>
#include <utility>

#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject(parent) {

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 8880)) {
        qDebug() << "Unable to start the server";
        tcpServer->close();
        return;
    }
    connect(tcpServer, &QTcpServer::newConnection, this, &Handler::handleConnection);

    QString ipAddr;
    QList<QHostAddress> ipAddrList = QNetworkInterface::allAddresses();
    for(auto it : ipAddrList) {
        if(it != QHostAddress::LocalHost && it.toIPv4Address()) {
            ipAddr = it.toString();
            break;
        }
    }
    if(ipAddr.isEmpty()) {
        ipAddr = QHostAddress(QHostAddress::LocalHost).toString();
    }

    qDebug() << "serverAddress: " << ipAddr;
    qDebug() << "serverPort: " << tcpServer->serverPort() << "\n";

    initialiseData(_data);
}

Handler::~Handler() { }

void Handler::handleConnection() {
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    clientConnection->waitForReadyRead(-1);

    QByteArray inData = clientConnection->readAll();
    qDebug() << "inData: " << inData;

    QJsonDocument inDoc(QJsonDocument::fromJson(inData));
    handleData(inDoc.object(), clientConnection);

    clientConnection->disconnectFromHost();
}

void Handler::handleData(const QJsonObject &json, QTcpSocket *socket) {
    if(json.contains("rqsttype") && json["rqsttype"].isDouble()) {
      RqstType type = static_cast<RqstType>(json["rqsttype"].toInt());
      switch(type) {
        case RqstType::CONNECTION: doConnectNewPlayer(socket, json["port"].toInt());
          break;
        case RqstType::MOVE: doCheckMove(json, socket);
          break;
      }
    }
    else {
      return;
    }
}

void Handler::sendDeny(QTcpSocket *socket) {
    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::DENY);

    QJsonDocument outDoc(json);
    socket->write(outDoc.toJson());
    if(!socket->waitForBytesWritten(-1))
      qDebug() << "sendDeny() couldn't send DENY to host: " << socket->peerAddress();
}

void Handler::sendUpd(int intFrom, int intTo) {
    Player *playerToUpd =
        (_activePlayer->port == _whitePlayer.port) ? &_blackPlayer : &_whitePlayer;

    QTcpSocket *socket = new QTcpSocket(this);
    //auto socket = std::make_unique<QTcpSocket>(this);
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    socket->connectToHost(playerToUpd->addr, playerToUpd->port);
    if(!socket->waitForConnected())
        qDebug() << "sendUpd() not connected to host: " << playerToUpd->addr;

    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::UPDATE);
    json["intfrom"] = static_cast<double>(intFrom);
    json["intto"] = static_cast<double>(intTo);

    QJsonDocument outDoc(json);
    socket->write(outDoc.toJson());
    if(!socket->waitForBytesWritten())
        qDebug() << "sendUpd() has not written bytes to host: " << playerToUpd->addr << "\n";

    socket->disconnectFromHost();
}

void Handler::sendUpdEnPassant(int intFrom, int intTo, int intToDelete) {
    Player *playerToUpd =
        (_activePlayer->port == _whitePlayer.port) ? &_blackPlayer : &_whitePlayer;

    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    socket->connectToHost(playerToUpd->addr, playerToUpd->port);
    if(!socket->waitForConnected())
        qDebug() << "sendUpd() not connected to host: " << playerToUpd->addr;

    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::UPDATE_EN_PASSAN);
    json["intfrom"] = static_cast<double>(intFrom);
    json["intto"] = static_cast<double>(intTo);
    json["inttodelete"] = static_cast<double>(intToDelete);

    QJsonDocument outDoc(json);
    socket->write(outDoc.toJson());
    if(!socket->waitForBytesWritten())
        qDebug() << "sendUpdEnPassant() has not written bytes to host: " << playerToUpd->addr << "\n";

    socket->disconnectFromHost();
}

void Handler::sendCorrect(QTcpSocket *socket) {
    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::CORRECT);
    QJsonDocument outDoc(json);
    socket->write(outDoc.toJson());
    if(socket->waitForBytesWritten())
        qDebug() << "doCheckMove() has sent CORRECT to host: " << socket->peerAddress() << "\n";
}

void Handler::sendCorrectEnPassant(QTcpSocket *socket, int intToDelete) {
    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::CORRECT_EN_PASSANT);
    json["inttodelete"] = static_cast<double>(intToDelete);
    QJsonDocument outDoc(json);
    socket->write(outDoc.toJson());
    if(socket->waitForBytesWritten())
        qDebug() << "doCheckMove() has sent CORRECT_EN_PASSANT to host: " << socket->peerAddress() << "\n";
}

void Handler::doConnectNewPlayer(QTcpSocket *socket, qint16 port) {
    if(isPlayersConnected()) {
      sendDeny(socket);
    }
    if(_whitePlayer.addr.isNull()) {
      _whitePlayer.addr = socket->peerAddress();
      _whitePlayer.port = port;
      _whitePlayer.color = PieceColor::WHITE_COLOR;
      qDebug() << "_whitePlayer.addr: " << _whitePlayer.addr;
      qDebug() << "_whitePlayer.port: " << _whitePlayer.port << "\n";

      QJsonObject json;
      json["answrtype"] = static_cast<double>(AnswrType::SUCCESS);
      json["playercolor"] = static_cast<double>(PieceColor::WHITE_COLOR);
      QJsonDocument outDoc(json);
      socket->write(outDoc.toJson());
      socket->waitForBytesWritten();
    }
    else {
      _blackPlayer.addr = socket->peerAddress();
      _blackPlayer.port = port;
      _blackPlayer.color = PieceColor::BLACK_COLOR;
      _playersConnected = true;
      _activePlayer = &_whitePlayer;
      qDebug() << "_blackPlayer.addr: " << _blackPlayer.addr;
      qDebug() << "_blackPlayer.port: " << _blackPlayer.port << "\n";

      QJsonObject json;
      json["answrtype"] = static_cast<double>(AnswrType::SUCCESS);
      json["playercolor"] = static_cast<double>(PieceColor::BLACK_COLOR);
      QJsonDocument outDoc(json);
      socket->write(outDoc.toJson());
      socket->waitForBytesWritten();
    }
}

bool Handler::checkConditions(const QJsonObject &json, QTcpSocket *socket) {
    if(!isPlayersConnected()) {
        qDebug() << "isPlayersConnected false" << "\n";
        return false;
    }
    if(!(json.contains("intfrom") && json["intfrom"].isDouble()))
        return false;
    if(!(json.contains("intto") && json["intto"].isDouble()))
        return false;
    if(!(json.contains("port") && json["port"].isDouble()))
        return false;
    if(_activePlayer->port != json["port"].toInt()
        || _activePlayer->addr != socket->peerAddress()) {
        qDebug() << "not activePlayer" << "\n";
        return false;
    }
    Square sq(json["intfrom"].toInt());
    const Piece *p = _data.at(sq);
    if(p == nullptr || _activePlayer->color != p->color()) {
        qDebug() << "activePlayer but wrong piece" << "\n";
        return false;
    }
    return true;
}

void Handler::doCheckMove(const QJsonObject &json, QTcpSocket *socket) {
    if(!checkConditions(json, socket)) {
        qDebug() << "checkConditions false" << "\n";
        sendDeny(socket);
        return;
    }
    qDebug() << "doCheckMove is called" << "\n";

    int intFrom = json["intfrom"].toInt();
    int intTo = json["intto"].toInt();

    Square squareFrom(intFrom);
    Square squareTo(intTo);

    const Piece *pieceFrom = _data.at(squareFrom);
    Squares moves = pieceFrom->moves(squareFrom, &_data);
    PieceType pieceType = pieceFrom->type();
    qDebug() << "pieceType is " << static_cast<int>(pieceFrom->type()) << "\n";
    switch(pieceType) {
        case PieceType::PAWN: if(!_validator.isPawnMoveValid(moves, squareFrom, squareTo)) {
                                  sendDeny(socket);
                                  qDebug() << "isPawnMoveValid false" << "\n";
                              }
                              else {
                                  if(_validator.isEnPassantPossible()) {
                                      int intToDelete = _validator.getEnPassantPiece();
                                      Square squareToDelete(intToDelete);
                                      sendCorrectEnPassant(socket, intToDelete);
                                      sendUpdEnPassant(intFrom, intTo, intToDelete);
                                      changeModel(squareFrom, squareTo);
                                      changeModel(squareToDelete, Square(-1));
                                      changeActivePlayer();
                                  }
                                  else {
                                      sendCorrect(socket);
                                      sendUpd(intFrom, intTo);
                                      changeModel(squareFrom, squareTo);
                                      changeActivePlayer();
                                  }
                              }
                              break;
        default: if(!_validator.isOrdinaryMoveValid(moves, squareTo)) {
                     sendDeny(socket);
                     qDebug() << "isOrdinaryMoveValid false" << "\n";
                 }
                 else {
                     sendCorrect(socket);
                     sendUpd(intFrom, intTo);
                     changeModel(squareFrom, squareTo);
                     changeActivePlayer();
                 }
                 break;
    }
}

void Handler::changeModel(const Square &squareFrom, const Square &squareTo) {
    if(squareTo.index() == -1) {
        _data.remove(squareFrom);
    }
    else {
        _data.replace(squareFrom, squareTo);
    }
}

void Handler::changeActivePlayer() {
    _activePlayer =
        (_activePlayer->port == _whitePlayer.port) ? &_blackPlayer : &_whitePlayer;
}

bool Handler::isPlayersConnected() {
    return _playersConnected;
}

void Handler::initialiseData(Data &data) {
  data.clear();

  for(unsigned i = 0; i < BOARD_SIZE; ++i) {
      data.add<Pawn>(Square(6, i), PieceColor::WHITE_COLOR);
      data.add<Pawn>(Square(1, i), PieceColor::BLACK_COLOR);
  }

  data.add<Rook>(Square(7, 0), PieceColor::WHITE_COLOR);
  data.add<Rook>(Square(7, 7), PieceColor::WHITE_COLOR);

  data.add<Rook>(Square(0, 0), PieceColor::BLACK_COLOR);
  data.add<Rook>(Square(0, 7), PieceColor::BLACK_COLOR);

  data.add<Knight>(Square(7, 1), PieceColor::WHITE_COLOR);
  data.add<Knight>(Square(7, 6), PieceColor::WHITE_COLOR);

  data.add<Knight>(Square(0, 1), PieceColor::BLACK_COLOR);
  data.add<Knight>(Square(0, 6), PieceColor::BLACK_COLOR);

  data.add<Bishop>(Square(7, 2), PieceColor::WHITE_COLOR);
  data.add<Bishop>(Square(7, 5), PieceColor::WHITE_COLOR);

  data.add<Bishop>(Square(0, 2), PieceColor::BLACK_COLOR);
  data.add<Bishop>(Square(0, 5), PieceColor::BLACK_COLOR);

  data.add<Queen>(Square(7, 3), PieceColor::WHITE_COLOR);
  data.add<Queen>(Square(0, 3), PieceColor::BLACK_COLOR);

  data.add<King>(Square(7, 4), PieceColor::WHITE_COLOR);
  data.add<King>(Square(0, 4), PieceColor::BLACK_COLOR);
}
