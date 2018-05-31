#ifndef GAMEDES_H
#define GAMEDES_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPushButton>
#include "player.h"
#include "mapp.h"
#include "ui_gamedes.h"
#include "someonewon.h"


#define TOTALSIZE 100
#define EACH_LINE 10
#define BLOCK_SIZE 30

class Player;

namespace Ui {
class GameDes;
}

class GameDes : public QWidget
{
    Q_OBJECT

public:
    explicit GameDes(QWidget *parent = 0);
    void drawGameScreen();
    int coorToIndex(int x, int y);
    void paintBlock(int index, int p);
    void exchange();
    void playGame(int id);
    bool checkRect(int index);
    SomeoneWon* getSw(){return sw;}
    void restartGame();
    void clearAll(MapP** map_p);
    void refreshPlayer(Player* ptr);
    Player* p1_get(){return p1;}
    Player* p2_get(){return p2;}
    Player** get_players();
    ~GameDes();

private:
    Player* list[2];
    Ui::GameDes *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    Player *p1, *p2;
    MapP *p1_map[TOTALSIZE], *p2_map[TOTALSIZE];
    bool map1_fills[TOTALSIZE], map2_fills[TOTALSIZE];
    int width_view, height_view, space_between, magic_number, gameCounter;
    int scene_width;
    int scene_height;
    SomeoneWon* sw;

};

#endif // GAMEDES_H
