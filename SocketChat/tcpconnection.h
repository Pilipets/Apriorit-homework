#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QString>

struct MessageData{
    char senderName[10];
    char message[30];
    MessageData(const QString& name, const QString& message);
    MessageData() = default;
    void write(QTcpSocket *sock) const;
    bool read(QTcpSocket *sock);
};

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    TcpConnection(QObject *parent, QTcpSocket *socket); //using from server side

    bool connectedToServer() const;
    void sendMessage(const MessageData& message);
    void setName(const QString& name) {m_name = name;}
    QString getName() const{return m_name;}
signals:
    void clientMessageReceived(TcpConnection* sender, const MessageData& message);
private slots:
    void slotReadyRead();
    void slotClientDisconnected();
private:
    QTcpSocket *m_socket;
    QString m_name;
    bool m_connected;
};

#endif // TCPCONNECTION_H
