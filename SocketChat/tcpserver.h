#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<QObject>
#include<QString>
#include <QtNetwork/QTcpServer>
#include<QSet>
#include "tcpconnection.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

    bool startListening(quint16 port);
    void sendMessage(TcpConnection *sender, const MessageData &message);

private slots:
    void slotnewConnection();
    void slotMessageReceived(TcpConnection *sender, const MessageData& message);
signals:
    void displayMessage(const QString& message);
private:
    QTcpServer *m_server = nullptr;

    QSet<TcpConnection*> m_connections;
};

#endif // TCPSERVER_H
