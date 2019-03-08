#ifndef __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#include <QDebug>
#include <utility>

#include "data.h"
#include "player.h"

class QTcpServer;
class QTcpSocket;

class Handler : public QObject {
    Q_OBJECT

public:
    explicit Handler(QObject *parent = nullptr);
    ~Handler();

    Handler& operator=(const Handler&) = delete;
    Handler(const Handler&) = delete;

private slots:
    void handleConnection();

private:
    void handleData(const QJsonObject&, QTcpSocket*);
    void doConnectNewPlayer(QTcpSocket*, qint16);
    void doCheckMove(const QJsonObject&, QTcpSocket*);
    bool isPlayersConnected() { return _playersConnected; }

    bool checkJson(const QJsonObject&);
    void sendDeny(QTcpSocket*);
    void sendUpd(const QJsonObject&);

private:
    QTcpServer *tcpServer = nullptr;
    Data _data;
    Player _whitePlayer;
    Player _blackPlayer;
    Player *_activePlayer = nullptr;
    bool _playersConnected = false;
};

#endif //  __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
