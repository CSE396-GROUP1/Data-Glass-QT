#include "player.h"
#include <QtMultimedia/QMediaPlayer>
#include <QDir>
#include <iostream>
#include <options.h>
using namespace std;

Player::Player(QObject* parent) : QObject(parent){
    //rectItem->setBrush(Qt::blue);
    rectItem = new QGraphicsRectItem();
    drawFinished = false;
    isGameFinished = false;
    isGameOver = false;
}

Player::Player(int colorCode, int playerId,GameDes *gd){
    rectItem = new QGraphicsRectItem();

    this->playerId = playerId;

    this->gd = gd;

    drawFinished = false;
    isGameFinished = false;
    isGameOver = false;
}

void Player::setColor(int colorCode){
    switch(colorCode){
        case 1: rectItem->setBrush(Qt::blue); break;
        case 2: rectItem->setBrush(Qt::red); break;
        case 3: rectItem->setBrush(Qt::green); break;
        case 4: rectItem->setBrush(Qt::yellow); break;
    }

    myColor = colorCode;
}

void Player::playStepSound() {
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/step.wav"));
    player->setVolume(30);
    player->play();
}

void Player::goUp(){

    if(rectItem->y()-35 >= -385 && drawFinished == true){
        rectItem->setPos(rectItem->x(),rectItem->y()-35);
        gd->playGame(getId());
        playStepSound();

        if(rectItem->y() <= -385 && isGameFinished == false){
            isGameFinished = true;
            //qDebug() << "Oyun bitti";


            if(playerId == 1){
               gd->getSw()->p1_won();
               gd->getSw()->show();
               //qDebug() << "Oyun bitti";
            }

            else if(playerId == 2){
                gd->getSw()->p2_won();
                gd->getSw()->show();
            }

            restartGame();
            QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/game_over.wav"));
            player->setVolume(1000);
            player->play();

        }
    }

    else if(rectItem->y() <= -350 && drawFinished == false){
        drawFinished = true;
        rectItem->setPos(rectItem->x(),rectItem->y()-35);
        gd->exchange();
        gd->playGame(getId());

    }
    else if(rectItem->y()-35 >= -385 && drawFinished == false){
        rectItem->setPos(rectItem->x(),rectItem->y()-35);
        int x = get_x();
        int y = get_y();
        int index = gd->coorToIndex(x,y);
        gd->paintBlock(index, playerId);
        playStepSound();
    }
}

void Player::goDown(){


    if(rectItem->y()+35 <= 0 && drawFinished == false){
        rectItem->setPos(rectItem->x(),rectItem->y()+35);
        int x = get_x();
        int y = get_y();
        int index = gd->coorToIndex(x,y);
        gd->paintBlock(index, playerId);
        playStepSound();
    }

    if(rectItem->y()+35 <= 0 && drawFinished == true){
        rectItem->setPos(rectItem->x(),rectItem->y()+35);
        gd->playGame(getId());
        playStepSound();
    }
}


void Player::goLeft(){
    if(rectItem->x()-35 >= 0 && drawFinished == false){
        rectItem->setPos(rectItem->x()-35,rectItem->y());
        int x = get_x();
        int y = get_y();
        int index = gd->coorToIndex(x,y);
        gd->paintBlock(index, playerId);
        playStepSound();
    }

    if(rectItem->x()-35 >= 0 && drawFinished == true){
        rectItem->setPos(rectItem->x()-35,rectItem->y());
        gd->playGame(getId());
        playStepSound();
    }
}


void Player::goRight(){
    qDebug() << drawFinished;
    if(rectItem->x()+35 <= 315 && drawFinished == false){
        rectItem->setPos(rectItem->x()+35,rectItem->y());
        int x = get_x();
        int y = get_y();
        int index = gd->coorToIndex(x,y);
        gd->paintBlock(index, playerId);
        playStepSound();
    }

    if(rectItem->x()+35 <= 315 && drawFinished == true){
        rectItem->setPos(rectItem->x()+35,rectItem->y());
        gd->playGame(getId());
        playStepSound();
    }
}

Player::~Player(){
    delete rectItem;
}

void Player::restartGame(){
    gd->restartGame();
}
