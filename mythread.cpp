#include "mythread.h"
#include <QApplication>

MyThread::MyThread(GameDes* gamedes,int &threadSize,qintptr sd,QObject *parent):
    QThread(parent)
{
    this->gamedes = gamedes;
    this->threadSize = &threadSize;
    this->sd = sd;

    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->sd)){
        emit error(socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

}

bool MyThread::connectStatus[2] = {false,false};

void MyThread::run(){
    qDebug() << socket->socketDescriptor() << "Client Connected";
    exec();
}

void MyThread::connectToPlayer(int id){
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(goUpper()),getPlayer(id),SLOT(goUp()));
    connect(this,SIGNAL(goDowner()),getPlayer(id),SLOT(goDown()));
    connect(this,SIGNAL(goRighter()),getPlayer(id),SLOT(goRight()));
    connect(this,SIGNAL(goLefter()),getPlayer(id),SLOT(goLeft()));

    connect(this,SIGNAL(restartGame()),getPlayer(id),SLOT(restartGame()));
}

void MyThread::readyRead(){

    QByteArray data = socket->readAll();

    qDebug() << socket->socketDescriptor() << "Data in" << data;

    QByteArray result;

    mutex.lock();
    if(data[0] == CONNECT){
        playerID = (int)(data[1] - '0');
        MyThread::connectStatus[playerID] = true;
        qDebug() << MyThread::connectStatus[0];
        qDebug() << MyThread::connectStatus[1];
        connectToPlayer(playerID);
        //CONNECT
        if(MyThread::connectStatus[1 - playerID]){
            //DRAWING
            result.append(DRAWING);
            emit sendToOther(result);
            sendData(result);
        }
        else{
            //WAIT_FOR_DRAWING
            result.append(WAIT_FOR_DRAWING);
            sendData(result);
        }
    }
    /*else if(dataList[0] == "Reconnect"){
        MyThread::connectToPlayer(playerID);
        sendData(data);
    }*/
    else{
        handle(data);
    }
    mutex.unlock();
}


void MyThread::disconnected(){
    qDebug() << socket->socketDescriptor() << "Disconnected";
    socket->deleteLater();
    exit(0);
}


void MyThread::sendData(QByteArray data){
    qDebug() << "Kendine yolladi" << data;
    data.append('\0');
    socket->write(data, 2);
}


void MyThread::sendingFromOther(QByteArray data){
    qDebug()<< "digerinden geldi..." << data;
    data.append('\0');
    socket->write(data, 2);

}

void MyThread::handle(QByteArray data){

    QByteArray result;

    if(data[0] == REQUEST){ //// In case client does not receive state data, it requests for that
        if(data[1] == DRAWING){
            if(!getPlayer(playerID)->isDrawFinished() && connectStatus[1 - playerID]){
                result.append(DRAWING);
                sendData(result);
            }
            else{
                result.append(WAIT_FOR_DRAWING);
                sendData(result);
            }
        }
        else if(data[1] == MOVING){
            if(getPlayer(playerID)->isDrawFinished() && getPlayer(1 - playerID)->isDrawFinished()){
                result.append(MOVING);
                sendData(result);
            }
            else{
                result.append(WAIT_FOR_MOVING);
                sendData(result);
            }
        }
    }
    else if(data[0] == DRAWING ){
        if(!getPlayer(playerID)->isDrawFinished()){
            if(connectStatus[1 - playerID])
                doAction(data[1]);
            else{
                result.append(WAIT_FOR_DRAWING);
                sendData(result);
            }
        }
        if(getPlayer(playerID)->isDrawFinished()){
            if(!getPlayer(1 - playerID)->isDrawFinished()){
                //WAIT_FOR_MOVING
                result.append(WAIT_FOR_MOVING);
                sendData(result);
            }
            else{
                //MOVING
                result.append(MOVING);
                emit sendToOther(result);
                sendData(result);
            }
        }
    }
    else if (data[0] == MOVING){

        if((!getPlayer(playerID)->getGameFinished() && !getPlayer(1 - playerID)->getGameFinished()) &&
                (getPlayer(playerID)->isDrawFinished() && getPlayer(playerID)->isDrawFinished())){
            doAction(data[1]);
        }
    }
    else if(data[0] == RESTARTING){
        getPlayer(playerID)->setRestartPerm(true);
        if(getPlayer(playerID)->getRestartPerm() && getPlayer(1 - playerID)->getRestartPerm() &&
                (getPlayer(playerID)->getGameFinished() || getPlayer(1 - playerID)->getGameFinished()))
        {
            result.append(NEWGAME);
            sendData(result);
            emit sendToOther(result);

            emit restartGame();

            getPlayer(playerID)->setRestartPerm(false);
            getPlayer(1 - playerID)->setRestartPerm(false);
        }
    }
}

void MyThread::doAction(char action){

    QByteArray result;
    //result.append(MOVING);

    if(action == RIGHT){
        emit goRighter();
        result.append(SUCCESS);
        result.append(action);
    }
    else if(action == LEFT){
        emit goLefter();
        result.append(SUCCESS);
        result.append(action);
    }
    else if(action == UP){
        emit goUpper();
        result.append(SUCCESS);
        result.append(action);
    }
    else if(action == DOWN){
        emit goDowner();
        result.append(SUCCESS);
        result.append(action);
    }

    if(getPlayer(playerID)->getGameOver()){
        getPlayer(playerID)->setGameOver(false);
        QByteArray result;
        result.append(GAMEOVER);
        sendData(result);
    }
    else if(getPlayer(playerID)->getGameFinished()){
        //FINISHING
        QByteArray result1;
        QByteArray result2;
        result1.append(FINISHING);
        result1.append(SUCCESS);
        sendData(result1);
        result2.append(FINISHING);
        result2.append(FAIL);
        emit sendToOther(result2);
    }
    else
        sendData(result);
}

Player* MyThread::getPlayer(int id){
    return gamedes->get_players()[id];
}

