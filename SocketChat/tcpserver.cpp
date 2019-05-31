#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject (parent)
{
    m_server = new QTcpServer(this);

    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::slotnewConnection);
}

bool TcpServer::startListening(quint16 port)
{
    bool isListening = m_server->listen(QHostAddress::AnyIPv4, port);
    return isListening;
}

void TcpServer::sendMessage(TcpConnection *sender, const MessageData &data)
{
    QString senderName = data.senderName;
    foreach (TcpConnection *connection, m_connections)
    {
        if (connection->connectedToServer() && connection != sender)
            connection->sendMessage(data);
    }
}

void TcpServer::slotnewConnection()
{
    TcpConnection *connection = new TcpConnection(this, m_server->nextPendingConnection());
    m_connections.insert(connection);

    //connection->sendMessage("Server Init handshake");
    connect(connection, &TcpConnection::clientMessageReceived, this, &TcpServer::slotMessageReceived);
}

void TcpServer::slotMessageReceived(TcpConnection* sender, const MessageData& data)
{
    this->sendMessage(sender, data);
    emit displayMessage(QString(data.senderName) + ": " + QString(data.message));
}
