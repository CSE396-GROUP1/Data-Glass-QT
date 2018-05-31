#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "gamedes.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(GameDes*,QObject *parent = 0);
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    GameDes* gd;
    int threadSize;
    QList<MyThread*> threadList;

};

#endif // MYSERVER_H
