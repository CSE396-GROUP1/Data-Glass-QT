#ifndef CUSTOMRECT_H
#define CUSTOMRECT_H

#include "gamedes.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPainter>
#include <QObject>
#include <QDebug>

class GameDes;

class Player: public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject* parent = 0);
    Player(int,int,GameDes*);
    ~Player();
    int get_x(){return rectItem->x();}
    int get_y(){return rectItem->y();}
    int getId(){return playerId;}
    void setFinished(bool stat){drawFinished = stat;}
    QGraphicsRectItem* getRectItem(){return rectItem;}    
    bool getGameFinished(){return isGameFinished;}
    bool getGameOver(){return isGameOver;}
    GameDes* getGameDes(){return gd;}
    void setGameDes(GameDes* val){gd = val;}
    void setGameOver(bool val){isGameOver = val;}
    void setIsGameFinished(bool val){isGameFinished = val;}
    void setRectItem(QGraphicsRectItem* val){rectItem =val;}
    int getColor(){return myColor;}
    void setRestartPerm(bool value){restart_perm = value;}
    bool getRestartPerm(){return restart_perm;}
    void playStepSound();
    void setColor(int colorCode);

public slots:
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    bool isDrawFinished(){return drawFinished;}

    void restartGame();

private:
    QGraphicsRectItem* rectItem;
    GameDes *gd;
    int playerId;
    bool drawFinished;
    bool isGameFinished;
    bool isGameOver;
    int myColor;
    bool restart_perm;
};

#endif // CUSTOMRECT_H
