#include "myserver.h"

MyServer::MyServer(GameDes* gd,QObject *parent):
    QTcpServer(parent)
{
    this->gd = gd;
    threadSize = 0;
}


void MyServer::startServer(){

    if(!this->listen(QHostAddress::AnyIPv4,8081)){
        qDebug() << "Could not start server";
    }
    else{
        qDebug() << "Listening...";
    }

}

void MyServer::incomingConnection(qintptr socketDescriptor){

    qDebug() << socketDescriptor << "Connecting...";

    MyThread *thread = new MyThread(gd,threadSize,socketDescriptor,this);

    if(threadList.length() < 2)

        threadList.append(thread);

    if(threadList.length() == 2){
        connect(threadList[0],SIGNAL(sendToOther(QByteArray)),threadList[1],SLOT(sendingFromOther(QByteArray)));
        connect(threadList[1],SIGNAL(sendToOther(QByteArray)),threadList[0],SLOT(sendingFromOther(QByteArray)));
    }

    thread->start();

}
