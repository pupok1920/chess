#ifndef CHMESSAGEHANDLER_H
#define CHMESSAGEHANDLER_H

#include <QAbstractMessageHandler>

class ChMessageHandler : public QAbstractMessageHandler {
public:
    ChMessageHandler();
    QString statusMessage() const;
    int line() const;
    int column() const;

protected:
    void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier,
        const QSourceLocation &sourceLocation);

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

#endif // CHMESSAGEHANDLER_H
