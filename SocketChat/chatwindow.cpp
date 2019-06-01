#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    connect(ui->le_Client1, &QLineEdit::returnPressed, this, &ChatWindow::slotClientEnterPressed);
    connect(ui->le_Client2, &QLineEdit::returnPressed, this, &ChatWindow::slotClientEnterPressed);
    connect(ui->le_Client3, &QLineEdit::returnPressed, this, &ChatWindow::slotClientEnterPressed);



    this->Init();
    for(auto client: clients){
        connect(client, &TcpClient::displayMessage, this, &ChatWindow::slotClientMessageReceived);
    }

    connect(m_server, &TcpServer::displayMessage, this, &ChatWindow::slotServerMessageReceived);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::slotClientEnterPressed()
{
    QObject* obj = sender();
    QLineEdit* sender = qobject_cast<QLineEdit*>(obj);

    TcpClient* receiver = nullptr;

    if(sender == ui->le_Client1){
        receiver= clients[0];
    }
    else if (sender == ui->le_Client2) {
        receiver= clients[1];
    }
    else {
        receiver= clients[2];
    }
    receiver->sendMessage(sender->text());
    sender->clear();
}

void ChatWindow::slotClientMessageReceived(const QString &message)
{
    QObject* obj = sender();
    TcpClient* sender = qobject_cast<TcpClient*>(obj);

    QListWidget* receiver = nullptr;

    if(sender == clients[0]){
        receiver = ui->list_Client1;
    }
    else if (sender == clients[1]) {
        receiver = ui->list_Client2;
    }
    else {
        receiver = ui->list_Client3;
    }
    receiver->addItem(message);
}

void ChatWindow::slotServerMessageReceived(const QString &message)
{
    ui->list_Server->addItem(message);
}

void ChatWindow::Init()
{
    m_server = new TcpServer(this);

    if (m_server->startListening(5900))
        ui->list_Server->addItem("Server started.");
    else
        ui->list_Server->addItem("Server failed to start.");

    for(size_t i = 0; i < 3; ++i){
        clients.push_back(new TcpClient(this));
    }

    for(auto client: clients){
        if(client->connectTo("localhost", 5900))
            emit client->displayMessage("Connected.");
        else {
            emit client->displayMessage("Failed to connect.");
        }
    }
}
