#ifndef __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#define __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
#include <QDebug>
#include <utility>
#include "data.h"

class QTcpServer;

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
    Data _data;
    QTcpServer *tcpServer = nullptr;
};

#endif // __HandlerNJNBDJBNDLBNDLBNDKBNDKBNDKL__
