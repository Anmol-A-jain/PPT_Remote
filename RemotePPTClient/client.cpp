#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    serverClient = new QTcpSocket();

    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            ui->ip->setText(address.toString());
        }
    }
    ui->status->setText("<p align='center' style='color:#666666;'>Disconnected</p>" );

}

Client::~Client()
{
    delete ui;
}

void Client::connected()
{
    ui->status->setText("<p align='center' style='color:#666666;'>Connected</p>" );
}

void Client::disconneced()
{
    ui->status->setText("<p align='center' style='color:#666666;'>Disconnected</p>" );
}

void Client::on_next_button_clicked()
{
    serverClient->write("2");
}

void Client::on_Back_Button_clicked()
{
    serverClient->write("1");
}

void Client::on_pushButton_clicked()
{
    qDebug() << ui->ip->text();

    connect(serverClient,&QTcpSocket::connected,this,&Client::connected);
    connect(serverClient,&QTcpSocket::disconnected,this,&Client::disconneced);
    serverClient->connectToHost(ui->ip->text(),4444);
}

void Client::on_ip_returnPressed()
{
    emit on_pushButton_clicked();
}
