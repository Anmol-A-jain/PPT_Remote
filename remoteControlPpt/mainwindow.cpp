#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer();

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()) );

    if(server->listen(QHostAddress::Any,4444))
    {
        ui->status->setText( "<p align='center'><span style=' font-size:16pt;'>server started</span></p>");
    }

    const QHostAddress &localhost = QHostAddress::LocalHost;
    QString ipaddress;
    for(const QHostAddress &address : QNetworkInterface::allAddresses() )
    {
        if(address != localhost && address.protocol() == QAbstractSocket::IPv4Protocol )
        {
            ui->ip->setText("<p align='center'><span style=' font-size:16pt;'> " + address.toString() +"</span></p>");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    client = server->nextPendingConnection();

    connect(client,&QTcpSocket::disconnected,this,&MainWindow::disconnected);
    connect(client,&QTcpSocket::readyRead,this,&MainWindow::readyRead);

    ui->status->setText("<p align='center'><span style=' font-size:16pt;'> connected " + client->peerAddress().toString() +"</span></p>");
}

void MainWindow::readyRead()
{
    QString data = QString( client->readAll() );
    int action = 0;
    if(data.contains('1'))
    {
        action = 1;
    }
    if(data.contains('2'))
    {
        action = 2;
    }

    qDebug() << action;

    switch (action)
    {
        case 1 :
        {

            // Simulating a left arrow keystroke
            keybd_event(VK_LEFT,0xCB,0 , 0); //left Press
            keybd_event(VK_LEFT,0xCB,KEYEVENTF_KEYUP,0); // left Release
            ui->textBrowser->append("Back");
            break;
        }
        case 2 :
        {
            // Simulating a right arrow keystroke
            keybd_event(VK_RIGHT,0xCD,0 , 0); //left Press
            keybd_event(VK_RIGHT,0xCD,KEYEVENTF_KEYUP,0); // left Release
            ui->textBrowser->append("Next");
            break;
        }

    }
}

void MainWindow::disconnected()
{
    //delete client;
    ui->status->setText("<p align='center'><span style=' font-size:16pt;'>Disconneced</span></p>");
}

