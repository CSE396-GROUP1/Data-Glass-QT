#include "painter.h"

QPainterPath::QPainterPath()
{
    shape();
}
QPainterPath shape() const override{
    QPainterPath path;
    QPolygon polygon;
    polygon << QPoint(0, 0);
    polygon << QPoint(5, 5);
    polygon << QPoint(10, 10);
    polygon << QPoint(10 - 5, 10 - 5);
    path.addPolygon(polygon);

    return path;
}
