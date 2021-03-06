#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include "functions.h"
#include <QString>

MyTcpServer::~MyTcpServer()
{
    foreach(int i, SClients.keys()) {
        QTextStream os(SClients[i]);
        SClients[i] -> close();
        SClients.remove(i);
    }
    server_status=0;
    mTcpServer->close();
    db.close();
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("seabattle");
    db.setUserName("postgres");
    db.setPassword("mabqteq5s2me");// здесь поставить пароль от базы данных, который вводится при запуске
    db.open();

}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        QTcpSocket* clientSocket = mTcpServer ->nextPendingConnection();
        int idusersocs=(int)clientSocket->socketDescriptor();
        SClients[idusersocs] = clientSocket;
        SClients[idusersocs] -> write("Hello, World!!! I am echo server!\r\n");
        connect(SClients[idusersocs], &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
        connect(SClients[idusersocs], &QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
  //  int id = (int)clientSocket->socketDescriptor();
    QByteArray array;
    std::string message="";
    while(clientSocket->bytesAvailable()>0)
    {
        array = clientSocket->readAll();
        message += array.toStdString();
    }

    qDebug()<<QString::fromStdString(message);

    std::string func = "";
    int field[200];
    int pos = message.find("&");
    func = message.substr(0, pos);
    message.erase(0, pos+1);
    if(func == "auth") {
        std::string log = "";
        std::string pass = "";
        pos = message.find("&");
        log = message.substr(0, pos);
        message.erase(0, pos);

        pos = message.find("&");
        pass = message.substr(pos+1, message.length() - 3);
        message.erase(0);

        qDebug()<<"login ="<<QString::fromStdString(log)
                <<"password = "<< QString::fromStdString(pass)
               <<"result = " << authorize(log,pass);
        array.clear();
        array.append(authorize(log,pass).toUtf8());
        clientSocket -> write(array);
    }
    if(func == "start") {

        array.clear();
        start(field);
        for(int i=0; i<200; i++)
            array.append(field[i]);
        qDebug()<<"field create";

        clientSocket -> write(array);
    }
    if(func == "stats") {
        QSqlQuery que;                           // подключение к бд
        QString number,wins,loses,shoots,aim,ships;
        que.exec("select * from players;");
        while (que.next())
    {
        number = que.value(0).toString();  // Номер игрока
        wins = que.value(1).toString();    // Количество побед
        loses = que.value(2).toString();   // Количество поражений
        shoots = que.value(3).toString();  // Количество выстрелов
        aim = que.value(4).toString();     // Количество попаданий
        ships = que.value(5).toString();   // Количество потопленных кораблей
        wins=wins+","+loses+","+shoots+","+aim+","+ships;
        stats[number.toLocal8Bit().constData()] = wins.toLocal8Bit().constData(); // Перечислены через запятую
    }
    }
    if(func == "set_coord") {
        set_coord(message, pos, field);
        qDebug()<<"field write in";
        array.clear();
        for(int i=0; i<200; i++) {
            array.append(field[i]);
        }
        qDebug()<<QString::fromStdString(message);
        clientSocket -> write(array);
    }
    if(func == "action"){
        int pos1 = message.find("6");
        QSqlQuery que;
                                                /*
                                                0 - пусто
                                                1 - мимо
                                                2 - ранил
                                                3 - убил
                                                4 - корабль
                                                5 - остров
                                                6 - отметка пользователя
                                                */
        switch (field[pos1]) {
            case 0:
                field[pos1] = 1;
               if (number==2)
               {
                que.exec("update players set shoots=shoots+1 where number =2"); // пустые выстрелы
                number=1;
               }
               else
                {
                que.exec("update players set shoots=shoots+1 where number =1");
                number=2;
               }
            break;
            case 4:
                if (field[pos1 - 1] == 4 || field[pos1 + 1] == 4 || field[pos1 - 10] == 4 || field[pos1 + 10] == 4)
                {
                    field[pos1] = 2;
                if (number==2)
                {
                que.exec("update players set shoots=shoots+1,aim=aim+1 where number =2"); // попадание
                number=1;
                }
                else
                {
                que.exec("update players set shoots=shoots+1,aim=aim+1 where number =1");
                number=2;
                }
                }
                else
                {
                    field[pos1] = 3;
                if (number==2)
                {
                que.exec("update players set shoots=shoots+1,aim=aim+1,ships=ships+1 where number =2"); // убил
                number=1;
                }
                else
                {
                que.exec("update players set shoots=shoots+1,aim=aim+1,ships=ships+1 where number =1");
                number=2;
                }
                }
                break;
            case 5:
                field[pos1] = 1;
               if (number==2)
               {
                que.exec("update players set shoots=shoots+1 where number =2"); // пустые выстрелы
                number=1;
               }
               else
                {
                que.exec("update players set shoots=shoots+1 where number =1");
                number=2;
               }
            break;

        int j = 0;
        for (int i=0; i<100; i++) {
            if (field[i] == 4) {
                j += 1;
                break;
            }
        }
            if (j != 0)
            {
               qDebug()<<"Game over, PLAYER 2 WIN";
               que.exec("update users set wins=wins+1 where number =2");
               que.exec("update users set loses=loses+1 where number =1");
               slotClientDisconnected();
            }
        j = 0;
        for (int i=100; i<200; i++) {
            if (field[i] == 4) {
                j += 1;
                break;
            }
        }
            if (j != 0)
            {
               qDebug()<<"Game over, PLAYER 1 WIN";
               que.exec("update users set wins=wins+1 where number =1");
               que.exec("update users set loses=loses+1 where number =2");
               slotClientDisconnected();
            }
        }
        qDebug()<<"action";
        array.clear();
        for(int i=0; i<200; i++) {
            array.append(field[i]);
        }
        clientSocket -> write(array);
    }
    if(func == "exit") {
        slotClientDisconnected();
    }
    //clientSocket -> write(array);
}
void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    int id = (int)clientSocket->socketDescriptor();
    clientSocket->close();
    SClients.remove(id);
    qDebug() << QString::fromUtf8("Client is disconnected \n");
}

/* 040400044404440404000044440000044004040004440040400044404440404000044440000044004040004440040400044404440&40400004444000004400404000444004040004440444040400004444000004400404000444000000444400444004040 */
