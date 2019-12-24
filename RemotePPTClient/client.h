#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void connected();
    void disconneced();
    void on_next_button_clicked();
    void on_Back_Button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Client *ui;
    QTcpSocket* serverClient;
};
#endif // CLIENT_H
