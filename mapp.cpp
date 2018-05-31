#include "mapp.h"

MapP::MapP(QObject* parent) : QObject(parent)
{
    rectItem = new QGraphicsRectItem();
    rectItem->setFlags(QGraphicsRectItem::ItemIsMovable | QGraphicsRectItem::ItemIsSelectable |
                       QGraphicsRectItem::ItemIsFocusable);

    rectItem->setAcceptHoverEvents(true);
    //rectItem->shape();
    rectItem->setBrush(Qt::white);
    isFilled = false;
    size = 30;
}

void MapP::fillRect(){

    isFilled = true;
    rectItem->setBrush(Qt::black);
}

void MapP::setNotFilled(){
    isFilled = false;
    rectItem->setBrush(Qt::white);


}

void MapP::set_x(int pos){
    pos_x = pos;
}

void MapP::set_y(int pos){
    pos_y = pos;
}

MapP::~MapP(){
    delete rectItem;
}
