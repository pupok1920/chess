#include <QtNetwork>
#include <QtCore>
#include <QByteArray>

#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject(parent) {

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, 8880)) {
    //if (!tcpServer->listen()) {
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

    qDebug() << "Piece: " << (int)pieceType;
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

    clientConnection->disconnectFromHost();
}
