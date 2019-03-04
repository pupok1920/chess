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
    qDebug() << "inData: " << inData;

    QJsonDocument inDoc(QJsonDocument::fromJson(inData));

    read(inDoc.object(), clientConnection);

    clientConnection->disconnectFromHost();
}

void Handler::read(const QJsonObject &json, QTcpSocket *socket) {
    if(json.contains("rqsttype") && json["rqsttype"].isDouble()) {
      RqstType type = static_cast<RqstType>(json["rqsttype"].toInt());
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
      _whitePlayer.port = socket->peerPort();
      _whitePlayer.color = PieceColor::WHITE_COLOR;

      QJsonObject json;
      json["answrtype"] = static_cast<double>(AnswrType::SUCCESS);
      json["playercolor"] = static_cast<double>(PieceColor::WHITE_COLOR);
      QJsonDocument outData(json);
      socket->write(outData.toJson());
    }
    else {
      _blackPlayer.addr = socket->peerAddress();
      _blackPlayer.port = socket->peerPort();
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
  //if(!(json.contains("colorto") && json["colorto"].isDouble()))
  //  sendDeny(socket);
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
  QJsonDocument outDoc(answrJson);
  socket->write(outDoc.toJson());
  socket->waitForBytesWritten();

  QJsonObject updJson;
  updJson["answrtype"] = static_cast<double>(AnswrType::UPDATE);
  updJson["intfrom"] = intFrom;
  updJson["intto"] = intTo;
  sendUpd(updJson, _activePlayer);

  _activePlayer =
    (_activePlayer->addr == _whitePlayer.addr) ? &_blackPlayer : &_whitePlayer;
}
