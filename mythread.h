#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QMutex>
#include "player.h"
#include <stdio.h>
#include "gamedes.h"

#define FAIL '0'
#define SUCCESS '1'
#define CONNECT '2'
#define WAIT_FOR_DRAWING '3'
#define DRAWING '4'
#define WAIT_FOR_MOVING '5'
#define MOVING '6'
#define FINISHING '7'
#define GAMEOVER '8'
#define RESTARTING '9'
#define NEWGAME 'N'

#define REQUEST 'R'

#define RIGHT '1'
#define LEFT '2'
#define UP '3'
#define DOWN '4'

using namespace std;

class MyThread : public QThread
{

    Q_OBJECT

public:
    explicit MyThread(GameDes* gamedes,int &threadSize, qintptr sd, QObject *parent = 0);
    void run();
    void sendData(QByteArray data);
    void handle(QByteArray str);
    void doAction(char action);

signals:
    void error(QTcpSocket::SocketError socketerror);
    void goUpper();
    void goLefter();
    void goRighter();
    void goDowner();
    void sendToOther(QByteArray data);

    void restartGame();

public slots:
    void sendingFromOther(QByteArray data);
    void readyRead();
    void disconnected();

private:
    GameDes* gamedes;
    QTcpSocket *socket;
    QMutex mutex;
    int* threadSize;
    qintptr sd;
    int playerID;
    static bool connectStatus[2];

    void connectToPlayer(int id);
    Player* getPlayer(int id);
};

#endif // MYTHREAD_H
