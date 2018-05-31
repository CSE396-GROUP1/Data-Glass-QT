#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include "ui_mainwindow.h"
#include "gamedes.h"
#include "buttons.h"
#include "options.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMediaPlayer *playerMain = new QMediaPlayer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGamedes(GameDes *gdInp);
    //MainWindow* getMw(){return this;}

private slots:
    void on_button_play_clicked();
    void on_button_exit_clicked();
    void on_button_options_clicked();

private:
    Ui::MainWindow *ui;
    GameDes* gd;
    Options* options;
};

#endif // MAINWINDOW_H
