#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"
#include "tcpclient.h"
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private slots:
    void slotClientEnterPressed();

    void slotClientMessageReceived(const QString &message);
    void slotServerMessageReceived(const QString &message);
private:
    Ui::ChatWindow *ui;

    TcpServer *m_server;
    QVector<TcpClient*> clients;
    void Init();
};

#endif // CHATWINDOW_H
