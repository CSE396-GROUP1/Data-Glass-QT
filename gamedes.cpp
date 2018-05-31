#include "gamedes.h"
#include <string>
#include <QDir>
#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <iostream>

using namespace std;

GameDes::GameDes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDes)
{
    ui->setupUi(this);
    gameCounter = 1;
    width_view = 800;
    height_view = 500;
    space_between = 5;
    magic_number = 50;
    p1 = new Player(1,1,this);
    p2 = new Player(2,2,this);
    scene_width = width_view - magic_number;
    scene_height = height_view - magic_number;
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::lightGray);
    scene->setSceneRect(0, 0, scene_width, scene_height);
    view = new QGraphicsView(scene);
    sw = new SomeoneWon();
}

Player** GameDes::get_players(){

    list[0] = p1_get();
    list[1] = p2_get();
    return list;
}

void GameDes::drawGameScreen(){

    int posx = 0;
    int posy = 0;


    int index = 0;
    int limit = EACH_LINE;
    for(int i = 0; i < EACH_LINE; i++){
        posx = 0;
        while(index < limit){
            p1_map[index] = new MapP();
            p1_map[index]->set_x(posx);
            p1_map[index]->set_y(posy);
            p1_map[index]->getRectItem()->setRect(p1_map[index]->get_x(), p1_map[index]->get_y(), p1_map[index]->getSize(), p1_map[index]->getSize());
            //
            scene->addItem(p1_map[index]->getRectItem());

            posx += p1_map[index]->getSize()+space_between;
            index++;
        }

        posy += p1_map[i]->getSize() + space_between;
        limit += EACH_LINE;
    }

    posx += magic_number + space_between;
    int p1_place = posy;
    posy = 0;

    int defaultx = posx;

    index = 0;
    limit = EACH_LINE;

    for(int i = 0; i < EACH_LINE; i++){
        while(index < limit){
            p2_map[index] = new MapP();
            p2_map[index]->getRectItem()->setRect(posx, posy, p2_map[index]->getSize(), p2_map[index]->getSize());
            scene->addItem(p2_map[index]->getRectItem());
            posx += p2_map[index]->getSize()+space_between;
            index++;
        }
        posy += p1_map[i]->getSize() + space_between;
        posx = defaultx;
        limit += EACH_LINE;
    }


    qDebug("%d\n", defaultx);
    qDebug("%d\n", p1_place);
    p1->getRectItem()->setRect(0,p1_place,BLOCK_SIZE,BLOCK_SIZE);
    p2->getRectItem()->setRect(defaultx, p1_place, BLOCK_SIZE, BLOCK_SIZE);

    scene->addItem(p1->getRectItem());
    scene->addItem(p2->getRectItem());


    view->setFixedSize(width_view,height_view);

    view->show();
}

void GameDes::exchange(){
    if(p1->isDrawFinished() && p2->isDrawFinished()){

        QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/go.wav"));
        player->setVolume(30);
        player->play();


        for(int i = 0; i < TOTALSIZE; i++){
            map1_fills[i] =  p1_map[i]->getFilled();
            map2_fills[i] =  p2_map[i]->getFilled();
        }

        clearAll(p1_map);
        clearAll(p2_map);

        scene->removeItem(p1->getRectItem());
        scene->removeItem(p2->getRectItem());

        refreshPlayer(p1);
        refreshPlayer(p2);

        list[0] = p1;
        list[1] = p2;

        p1->getRectItem()->setRect(0,350,BLOCK_SIZE,BLOCK_SIZE);
        p2->getRectItem()->setRect(405,350, BLOCK_SIZE, BLOCK_SIZE);

        p1->setFinished(true);
        p2->setFinished(true);

        scene->addItem(p1->getRectItem());
        scene->addItem(p2->getRectItem());
    }

}

void GameDes::clearAll(MapP** map_p){
    for(int i = 0; i < TOTALSIZE; i++){
        map_p[i]->setNotFilled();
    }
}

void GameDes::playGame(int id){

    if(id == 1){
        int x = p1->get_x();
        int y = p1->get_y();
        int index = coorToIndex(x,y);
        if(checkRect(index)){
            if(map2_fills[index] == true)
                paintBlock(index, id);
            else{
                scene->removeItem(p1->getRectItem());

                QMediaPlayer *player = new QMediaPlayer;
                player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/restart.wav"));
                player->setVolume(1000);
                player->play();

                refreshPlayer(p1);
                p1->getRectItem()->setRect(0,350,BLOCK_SIZE,BLOCK_SIZE);
                p1->setFinished(true);
                scene->addItem(p1->getRectItem());
                clearAll(p1_map);
                p1->setGameOver(true);
            }
        }
    }

    else if(id == 2){
        int x = p2->get_x();
        int y = p2->get_y();
        int index = coorToIndex(x,y);
        if(checkRect(index)){
            if(map1_fills[index] == true)
                paintBlock(index, id);
            else{
                scene->removeItem(p2->getRectItem());

                QMediaPlayer *player = new QMediaPlayer;
                player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/restart.wav"));
                player->setVolume(1000);
                player->play();

                refreshPlayer(p2);
                p2->getRectItem()->setRect(405,350, BLOCK_SIZE, BLOCK_SIZE);
                p2->setFinished(true);
                scene->addItem(p2->getRectItem());
                clearAll(p2_map);
                p2->setGameOver(true);
            }
        }
    }

}

bool GameDes::checkRect(int index){
    if(index >= 0 && index < 100){
        return true;
    }

    return false;
}

int GameDes::coorToIndex(int x, int y){
    int tmp = y/(BLOCK_SIZE+space_between);
    tmp = tmp + 10;
    tmp = tmp * 10;
    tmp = tmp + x/(BLOCK_SIZE+space_between);
    return tmp;
}

void GameDes::paintBlock(int index, int p){
    //qDebug() << "Boyaniyor:" << index;
    if(index < 100 && index >=0){
        if(p == 1){
            p1_map[index]->fillRect();
        }
        else{
            p2_map[index]->fillRect();
        }
    }
}

void GameDes::refreshPlayer(Player *ptr){

    delete ptr->getRectItem();

    ptr->setRectItem(new QGraphicsRectItem);
    if (ptr->getId() == 1){
        ptr->setColor(ptr->getColor());
    }
    else if (ptr->getId() == 2){
        ptr->setColor(ptr->getColor());
    }

    ptr->setGameOver(false);
    ptr->setFinished(false);
    ptr->setIsGameFinished(false);

}

void GameDes::restartGame(){

    if(p1->getGameFinished() || p2->getGameFinished()){

        for(int i = 0; i < TOTALSIZE; i++){
            scene->removeItem(p1_map[i]->getRectItem());
            delete p1_map[i];
        }

        for(int i = 0; i < TOTALSIZE; i++){
            scene->removeItem(p2_map[i]->getRectItem());
            delete p2_map[i];
        }

        refreshPlayer(p1);
        refreshPlayer(p2);

        gameCounter++;

        drawGameScreen();
    }

}

GameDes::~GameDes()
{
    delete ui;
    delete sw;
    delete p1;
    delete p2;
    for(int i = 0; i < TOTALSIZE; i++){
        delete p1_map[i];
    }
    for(int i = 0; i < TOTALSIZE; i++){
        delete p2_map[i];
    }

    delete scene;
    delete view;
}
