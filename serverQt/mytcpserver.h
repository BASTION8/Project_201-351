#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlRecord>
#include <QSql>
#include <map>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlField>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
    QSqlDatabase db;
    QMap<std::string, std::string> stats;
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    int server_status;
    int number=1;
    QMap<int, QTcpSocket *> SClients;
};
#endif // MYTCPSERVER_H







