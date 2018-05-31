#ifndef MAPP1_H
#define MAPP1_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QPainter>
#include <QPainterPath>

class MapP: public QObject
{
    Q_OBJECT
public:
    explicit MapP(QObject* parent = 0);
    ~MapP();
    void fillRect();
    int getSize(){return size;}
    bool getFilled(){return isFilled;}
    void setNotFilled();
    QGraphicsRectItem* getRectItem(){return rectItem;}
    QPainterPath item;
    void set_x(int pos);
    void set_y(int pos);
    int get_x(){return pos_x;}
    int get_y(){return pos_y;}

private:
    bool isFilled;
    int size, pos_x, pos_y;
    QGraphicsRectItem* rectItem;

};

#endif // MAPP1_H
