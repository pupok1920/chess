#include <QtNetwork>
#include <QtCore>
#include <QByteArray>

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
    else
      return;
}

void Handler::sendDeny(QTcpSocket *s) {
    QJsonObject json;
    json["answrtype"] = static_cast<double>(AnswrType::DENY);

    QJsonDocument outDoc(json);
    s->write(outDoc.toJson());
    if(s->waitForBytesWritten(-1))
      qDebug() << "sendDeny() has send DENY to host: " << s->peerAddress();
    else
      qDebug() << "sendDeny() couldn't send DENY to host: " << s->peerAddress();
}

void Handler::sendUpd(const QJsonObject &json) {
  Player *playerToUpd =
    (_activePlayer->port == _whitePlayer.port) ? &_blackPlayer : &_whitePlayer;

  QTcpSocket *socket = new QTcpSocket(this);
  connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

  socket->connectToHost(playerToUpd->addr, playerToUpd->port);
  if(socket->waitForConnected())
    qDebug() << "sendUpd() connected to host: " << playerToUpd->addr;
  else
    qDebug() << "sendUpd() not connected to host: " << playerToUpd->addr;

  QJsonDocument outDoc(json);
  socket->write(outDoc.toJson());
  if(socket->waitForBytesWritten())
    qDebug() << "sendUpd() has written bytes to host: " << playerToUpd->addr << "\n";
  else
    qDebug() << "sendUpd() has not written bytes to host: " << playerToUpd->addr << "\n";

  socket->disconnectFromHost();
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

bool Handler::checkJson(const QJsonObject &json) {
  if(!(json.contains("colorfrom") && json["colorfrom"].isDouble()))
    return false;
  if(json.contains("colorto"))
    if(!json["colorto"].isDouble())
      return false;
  if(!(json.contains("piecetype") && json["piecetype"].isDouble()))
    return false;
  if(!(json.contains("intfrom") && json["intfrom"].isDouble()))
    return false;
  if(!(json.contains("intto") && json["intto"].isDouble()))
    return false;
  if(!(json.contains("port") && json["port"].isDouble()))
    return false;
  return true;
}

void Handler::doCheckMove(const QJsonObject &json, QTcpSocket *socket) {
  if(!isPlayersConnected()) {
    sendDeny(socket);
    qDebug() << "isPlayersConnected" << "\n";
    return;
  }
  if(!checkJson(json)) {
    sendDeny(socket);
    qDebug() << "checkJson" << "\n";
    return;
  }
  if(_activePlayer->port != json["port"].toInt()) {
    sendDeny(socket);
    qDebug() << "not your piece 1" << "\n";
    return;
  }
  if(_activePlayer->port == json["port"].toInt()
      && _activePlayer->color != static_cast<PieceColor>(json["colorfrom"].toInt())) {
    sendDeny(socket);
    qDebug() << "not your piece 2" << "\n";
    return;
  }
  if(_activePlayer->addr != socket->peerAddress()) {
    sendDeny(socket);
    qDebug() << "not activePlayer" << "\n";
    return;
  }
  if(_activePlayer->color != static_cast<PieceColor>(json["colorfrom"].toInt())) {
    sendDeny(socket);
    qDebug() << "activePlayer but not your piece" << "\n";
    return;
  }
  if(json.contains("colorto"))
    if(json["colorfrom"].toInt() == json["colorto"].toInt()) {
      sendDeny(socket);
      qDebug() << "same PieceColor" << "\n";
      return;
    }

  ///PieceType pieceType = static_cast<PieceType>(json["piecetype"].toInt());
  int intFrom = json["intfrom"].toInt();
  int intTo = json["intto"].toInt();

  int oldX = intFrom % BOARD_SIZE;
  int oldY = intFrom / BOARD_SIZE;
  int newX = intTo % BOARD_SIZE;
  int newY = intTo / BOARD_SIZE;

  Square squareFrom = static_cast<Square>(intFrom);
  //auto piece = std::make_shared<Piece>(_data.at(squareFrom));
  auto piece = _data.at(squareFrom);
  if(!piece)
      qDebug() << "*piece is \"false\"";
  if(!piece->isMoveValid(oldX, oldY, newX, newY)) {
    sendDeny(socket);
    qDebug() << "isMoveValid false" << "\n";
    return;
  }

  QJsonObject answrJson;
  answrJson["answrtype"] = static_cast<double>(AnswrType::CORRECT);
  QJsonDocument outDoc(answrJson);
  socket->write(outDoc.toJson());
  if(socket->waitForBytesWritten())
    qDebug() << "doCheckMove() has sent CORRECT to host: " << socket->peerAddress();

  QJsonObject updJson;
  updJson["answrtype"] = static_cast<double>(AnswrType::UPDATE);
  updJson["intfrom"] = static_cast<double>(intFrom);
  updJson["intto"] = static_cast<double>(intTo);
  sendUpd(updJson);

  Square squareTo = static_cast<Square>(intTo);
  changeModel(squareFrom, squareTo);
}

void Handler::changeModel(const Square &squareFrom, const Square &squareTo) {
    _data.replace(squareFrom, squareTo);
    _activePlayer =
        (_activePlayer->port == _whitePlayer.port) ? &_blackPlayer : &_whitePlayer;
}
bool Handler::isPlayersConnected() {
    return _playersConnected;
}

void Handler::initialiseData(Data &data) {
    data.clear();

    for(unsigned i = 0; i < BOARD_SIZE; ++i) {
        data.add<Pawn>(Square(6, i));
        data.add<Pawn>(Square(1, i));
    }

    data.add<Rook>(Square(7, 0));
    data.add<Rook>(Square(7, 7));

    data.add<Rook>(Square(0, 0));
    data.add<Rook>(Square(0, 7));

    data.add<Knight>(Square(7, 1));
    data.add<Knight>(Square(7, 6));

    data.add<Knight>(Square(0, 1));
    data.add<Knight>(Square(0, 6));

    data.add<Bishop>(Square(7, 2));
    data.add<Bishop>(Square(7, 5));

    data.add<Bishop>(Square(0, 2));
    data.add<Bishop>(Square(0, 5));

    data.add<Queen>(Square(7, 3));
    data.add<Queen>(Square(0, 3));

    data.add<King>(Square(7, 4));
    data.add<King>(Square(0, 4));
}
