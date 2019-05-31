#include "tcpconnection.h"
#include<QDataStream>
#include<QtGlobal>
#include "tcpserver.h"
//usage for server; ctor
TcpConnection::TcpConnection(QObject *parent, QTcpSocket *socket):
    QObject(parent), m_socket(socket), m_connected(true)
{
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpConnection::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpConnection::slotClientDisconnected);
}

bool TcpConnection::connectedToServer() const
{
    return  m_connected;
}

//write message to the client, connected to m_socket
void TcpConnection::sendMessage(const MessageData &message)
{
    message.write(m_socket);
}

//read data from m_socket(both client,server usage)
void TcpConnection::slotReadyRead()
{
    MessageData receive;
    if(!receive.read(m_socket))
        return;

    //dynamic_cast<TcpServer*>(parent)->slotMessageReceived(receive);

    emit clientMessageReceived(this, receive);
}

void TcpConnection::slotClientDisconnected()
{
    m_connected = false;
    m_socket->deleteLater();
    m_socket = nullptr;
}

MessageData::MessageData(const QString &name, const QString &data)
{
    strncpy(this->senderName, name.toStdString().c_str(), 9);
    senderName[9] = '\0';
    strncpy(message, data.toStdString().c_str(), 29);
    message[29] = '\0';
}

void MessageData::write(QTcpSocket *sock) const
{
    sock->write(senderName,10);
    sock->write(message,30);
}

bool MessageData::read(QTcpSocket *sock)
{
    if(sock->bytesAvailable() < 40)
        return false;
    sock->read(senderName,10);
    sock->read(message,30);
    return true;
}
