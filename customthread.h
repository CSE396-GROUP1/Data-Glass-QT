#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QtCore>
#include <QThread>
#include "gamedes.h"
#include <QGraphicsScene>


class CustomThread: public QThread
{
public:
    CustomThread();
    void run();
};

#endif // CUSTOMTHREAD_H
