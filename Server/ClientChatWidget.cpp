#include "ClientChatWidget.h"
#include "ui_ClientChatWidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientChatWidget),
    _client(client)
{
    ui->setupUi(this);
    connect(_client, &QTcpSocket::readyRead, this, &ClientChatWidget::dataReceived);
    connect(_client, &QTcpSocket::disconnected, this, &ClientChatWidget::clientDisconnected);

}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::dataReceived()
{
    auto data = _client->readAll();
    ui->lstMessages->addItem(data);
}

void ClientChatWidget::on_btnSend_clicked()
{
    _client->write(ui->InMessage->text().trimmed().toUtf8());
    ui->InMessage->setText("");
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSend->setEnabled(false);
}
