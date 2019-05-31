#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include<QtNetwork/QTcpSocket>
#include "tcpconnection.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr); //using from client side
    ~TcpClient();

    bool connectTo(const QString &host, quint16 port);
    void sendMessage(const QString& message);

    bool connectedToServer() const;

signals:
    void displayMessage(const QString& message);
private slots:
    void slotReadyRead();
    void slotServerDisconnected();
private:
    static quint16 Amount;
    QString m_name;
    QTcpSocket *m_socket;
    bool m_connected;
};

#endif // TCPCLIENT_H
