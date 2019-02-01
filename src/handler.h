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

    Handler& operator=(Handler const&) = delete;
    Handler(Handler const&) = delete;

private slots:
    void handleConnection();

private:
    void read(const QJsonObject&, QTcpSocket*);
    void doConnectNewPlayer(QTcpSocket*);
    void doCheckMove(const QJsonObject&, QTcpSocket*);
    bool isPlayersConnected() { return _playersConnected; }

    void checkJson(const QJsonObject&, QTcpSocket*);
    void sendDeny(QTcpSocket*);
    void sendUpd(const QJsonObject&, const Player*);

private:
    QTcpServer *tcpServer = nullptr;
    Data _data;
    Player _whitePlayer;
    Player _blackPlayer;
    Player *_activePlayer = nullptr;
    bool _playersConnected = false;
};

#endif //  __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
