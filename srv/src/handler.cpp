#include <QtNetwork>
#include <QtCore>

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

    QByteArray inDataPieceType = clientConnection->readLine(2);
    QByteArray inDataFrom = clientConnection->readLine(2);
    QByteArray inDataTo = clientConnection->readLine(2);

    /*qDebug() << "pieceType is: " << inDataPieceType;
    qDebug() << "From is: " << inDataFrom;
    qDebug() << "To is: " << inDataTo;*/

    int intPieceType = inDataPieceType.toInt();
    //PieceType pieceType = PieceType(intPieceType);
    int draggedFrom = inDataFrom.toInt();
    int draggedTo = inDataTo.toInt();
    //int intPieceType = static_cast<int>(inDataPieceType);
    PieceType pieceType = static_cast<PieceType>(intPieceType);
    //int draggedFrom = static_cast<int>(inDataFrom);
    //int draggedTo = static_cast<int>(inDataTo);

    int oldX = draggedFrom % BOARD_SIZE;
    int oldY = draggedFrom / BOARD_SIZE;
    int newX = draggedTo % BOARD_SIZE;
    int newY = draggedTo / BOARD_SIZE;

    const Piece *pieceFrom = _data.type(pieceType);

    bool result = pieceFrom->isMoveValid(oldX, oldY, newX, newY);

    const char tr = 1;
    const char fls = 0;

    if(result)
      clientConnection->write(&tr);
    else
      clientConnection->write(&fls);

    clientConnection->disconnectFromHost();
}
