#ifndef __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__

#include "data.h"
#include "player.h"
#include "validator.h"

class QTcpServer;
class QTcpSocket;

class Square;

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
    void initialiseData(Data &);
    void handleData(const QJsonObject &, QTcpSocket *);
    void doConnectNewPlayer(QTcpSocket *, qint16);
    void doCheckMove(const QJsonObject &, QTcpSocket *);
    void changeModel(const Square &, const Square &);
    bool isPlayersConnected();

    bool checkConditions(const QJsonObject &, QTcpSocket *);
    void sendDeny(QTcpSocket *);
    void sendAnswrCor(QTcpSocket *);
    void sendUpd(int, int);

private:
    QTcpServer *tcpServer = nullptr;
    Data _data;
    Player _whitePlayer;
    Player _blackPlayer;
    Player *_activePlayer = nullptr;
    bool _playersConnected = false;
    Validator _validator;
};

#endif //  __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
