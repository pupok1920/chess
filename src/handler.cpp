#include <QtNetwork>
#include <QtCore>
#include <QByteArray>

#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject(parent) {

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, 8880)) {
        qDebug() << "Unable to start the server";
        tcpServer->close();
        return;
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &Handler::handleConnection);

    qDebug() << tcpServer->serverAddress();
    qDebug() << tcpServer->serverPort();

}

Handler::~Handler() { }

void Handler::handleConnection() {
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);

    clientConnection->waitForReadyRead(-1);

    QByteArray inData = clientConnection->readAll();
    //qDebug() << "ba: " << ba;

    QJsonDocument inDoc(QJsonDocument::fromJson(inData));

    read(inDoc.object(), clientConnection);

    clientConnection->disconnectFromHost();


    /*QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);

    clientConnection->waitForReadyRead(-1);

    //QByteArray ba = clientConnection->readAll();
    //qDebug() << "ba: " << ba;

    QByteArray inDataPieceType = clientConnection->read(4);
    QByteArray inDataFrom = clientConnection->read(4);
    QByteArray inDataTo = clientConnection->read(4);

    qDebug() << "pieceType is: " << inDataPieceType;
    qDebug() << "from is: " << inDataFrom;
    qDebug() << "to is: " << inDataTo;

    char chrPieceType = inDataPieceType[3];
    char chrDraggedFrom = inDataFrom[3];
    char chrDraggedTo = inDataTo[3];
    //int intPieceType = static_cast<int>(inDataPieceType);

    PieceType pieceType = static_cast<PieceType>(chrPieceType);
    int draggedFrom = static_cast<int>(chrDraggedFrom);
    int draggedTo = static_cast<int>(chrDraggedTo);

    qDebug() << "Piece: " << static_cast<int>(pieceType);
    qDebug() << "From: " << draggedFrom;
    qDebug() << "To: " << draggedTo;

    int oldX = draggedFrom % BOARD_SIZE;
    int oldY = draggedFrom / BOARD_SIZE;
    int newX = draggedTo % BOARD_SIZE;
    int newY = draggedTo / BOARD_SIZE;

    qDebug() << oldX;
    qDebug() << oldY;
    qDebug() << newX;
    qDebug() << newY;

    const Piece *pieceFrom = _data.type(pieceType);

    bool result = pieceFrom->isMoveValid(oldX, oldY, newX, newY);

    const char tr = 1;
    const char fls = 0;

    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);

    if(result) {
      out << tr;
    }
    else {
      out << fls;
    }

    clientConnection->write(ba);
    qDebug() << "result is: " << (int)ba.at(3);

    if(clientConnection->waitForBytesWritten())
      qDebug() << "bytes were written";
    else
      qDebug() << "bytes were not written";

    clientConnection->disconnectFromHost();*/
}

void Handler::read(const QJsonObject &json, QTcpSocket *socket) {
    if(json.contains("type") && json["type"].isDouble()) {
      RqstType type = static_cast<RqstType>(json["type"].toInt());
      switch(type) {
        case RqstType::CONNECTION: doConnectNewPlayer(socket);
          break;
        case RqstType::MOVE: doCheckMove(json, socket);
          break;
      }
    }
    else
      return;
}

void Handler::sendDeny(QTcpSocket *s) {
    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::DENY);

    QJsonDocument outData(json);
    s->write(outData.toJson());
}

void Handler::sendUpd(const QJsonObject &json, const Player *activePlayer) {
  Player *playerToUpd =
    (activePlayer->addr == _whitePlayer.addr) ? &_blackPlayer : &_whitePlayer;

  QTcpSocket *socket = new QTcpSocket(this);
  connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

  socket->connectToHost(playerToUpd->addr, playerToUpd->port);
  socket->waitForConnected();

  QJsonDocument outData(json);
  socket->write(outData.toJson());
  socket->waitForBytesWritten();

  socket->disconnectFromHost();
}

void Handler::doConnectNewPlayer(QTcpSocket *socket) {
    if(isPlayersConnected()) {
      sendDeny(socket);
    }
    else if(_whitePlayer.addr.isNull()) {
      _whitePlayer.addr = socket->peerAddress();
      _whitePlayer.color = PieceColor::WHITE_COLOR;

      QJsonObject json;
      json["answrtype"] = static_cast<double>(AnswrType::SUCCESS);
      json["playercolor"] = static_cast<double>(PieceColor::WHITE_COLOR);
      QJsonDocument outData(json);
      socket->write(outData.toJson());
    }
    else {
      _blackPlayer.addr = socket->peerAddress();
      _blackPlayer.color = PieceColor::WHITE_COLOR;
      _playersConnected = true;
      _activePlayer = &_whitePlayer;

      QJsonObject json;
      json["answrtype"] = static_cast<double>(AnswrType::SUCCESS);
      json["playercolor"] = static_cast<double>(PieceColor::BLACK_COLOR);
      QJsonDocument outData(json);
      socket->write(outData.toJson());
    }
}

void Handler::checkJson(const QJsonObject &json, QTcpSocket *socket) {
  if(!(json.contains("colorfrom") && json["colorfrom"].isDouble()))
    sendDeny(socket);
  if(!(json.contains("colorto") && json["colorto"].isDouble()))
    sendDeny(socket);
  if(!(json.contains("piecetype") && json["piecetype"].isDouble()))
    sendDeny(socket);
  if(!(json.contains("intfrom") && json["intfrom"].isDouble()))
    sendDeny(socket);
  if(!(json.contains("intto") && json["intto"].isDouble()))
    sendDeny(socket);
}

void Handler::doCheckMove(const QJsonObject &json, QTcpSocket *socket) {
  if(!isPlayersConnected())
    sendDeny(socket);
  checkJson(json, socket);
  if(_activePlayer->addr != socket->peerAddress())
    sendDeny(socket);
  if(_activePlayer->color != static_cast<PieceColor>(json["colorfrom"].toInt()))
    sendDeny(socket);
  if(json["colorfrom"].toInt() == json["colorto"].toInt())
    sendDeny(socket);

  PieceType pieceType = static_cast<PieceType>(json["piecetype"].toInt());
  int intFrom = json["intfrom"].toInt();
  int intTo = json["intto"].toInt();

  int oldX = intFrom % BOARD_SIZE;
  int oldY = intFrom / BOARD_SIZE;
  int newX = intTo % BOARD_SIZE;
  int newY = intTo / BOARD_SIZE;

  const Piece *piece = _data.type(pieceType);
  if(!piece->isMoveValid(oldX, oldY, newX, newY))
    sendDeny(socket);

  QJsonObject answrJson;
  answrJson["answrtype"] = static_cast<double>(AnswrType::CORRECT);
  QJsonDocument outData(answrJson);
  socket->write(outData.toJson());

  QJsonObject updJson;
  updJson["answrtype"] = static_cast<double>(AnswrType::UPDATE);
  updJson["intfrom"] = intFrom;
  updJson["intto"] = intTo;
  sendUpd(updJson, _activePlayer);

  _activePlayer =
    (_activePlayer->addr == _whitePlayer.addr) ? &_blackPlayer : &_whitePlayer;
}
