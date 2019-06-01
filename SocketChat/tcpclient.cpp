#include "tcpclient.h"
#include<QDataStream>

quint16 TcpClient::Amount = 0;

TcpClient::TcpClient(QObject *parent):
    QObject(parent), m_socket(new QTcpSocket(this))
{
    Amount += 1;
    m_name = "Client" + QString::number(Amount);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::slotServerDisconnected);
}

TcpClient::~TcpClient()
{
    if(m_socket)
        m_socket->disconnectFromHost();
    delete m_socket;
}

//connect to Server
bool TcpClient::connectTo(const QString &host, quint16 port)
{
    m_socket->connectToHost(host, port);
    m_connected = m_socket->waitForConnected(5000);

    this->sendMessage("Init connection");
    return m_connected;
}

//write message to the server, connected to m_socket
void TcpClient::sendMessage(const QString &message)
{
    MessageData toSend(m_name, message);
    toSend.write(m_socket);

    emit displayMessage("Me: " + message);
}

bool TcpClient::connectedToServer() const
{
    return m_connected;
}

void TcpClient::slotReadyRead()
{
    MessageData receive;
    while(m_socket->bytesAvailable()){
        if(!receive.read(m_socket))
            continue;

        emit displayMessage(QString(receive.senderName) + ": " + QString(receive.message));
    }
}

void TcpClient::slotServerDisconnected()
{
    m_connected = false;
    m_socket->deleteLater();
    m_socket = nullptr;
}
