#include "mainwindow.h"
#include "gamedes.h"
#include "myserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameDes gd;
    MainWindow w;
    w.setGamedes(&gd);
    MyServer server(&gd);
    server.startServer();
    w.show();

    return a.exec();
}
