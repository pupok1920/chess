#include "chmessagehandler.h"

/** \class ChMessageHandler
  \brief Message handler for XML Schema validation.

  Use statusMessage(), line() and column() to get information about error.
*/
ChMessageHandler::ChMessageHandler(): QAbstractMessageHandler(0)
{
}

QString ChMessageHandler::statusMessage() const
{
    return m_description;
}

int ChMessageHandler::line() const
{
    return m_sourceLocation.line();
}

int ChMessageHandler::column() const
{
    return m_sourceLocation.column();
}

void ChMessageHandler::handleMessage(QtMsgType type, const QString &description,
    const QUrl &identifier, const QSourceLocation &sourceLocation)
{

    Q_UNUSED(type);
    Q_UNUSED(identifier);

    m_messageType = type;
    m_description = description;
    m_sourceLocation = sourceLocation;
}
