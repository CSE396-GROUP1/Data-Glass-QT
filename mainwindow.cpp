#include "mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include <QtMultimedia/QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    QPixmap pix = QPixmap(":/background/space.jpg");


    playerMain->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/intro.mp3"));
    playerMain->setVolume(100);
    playerMain->play();

    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);
    options = new Options(this->gd);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGamedes(GameDes* gdInp){
    gd = gdInp;
}

void MainWindow::on_button_play_clicked(){

    playerMain->setVolume(40);

    Buttons* b = new Buttons();
    b->gdSetter(gd);

    gd->drawGameScreen();
    b->show();
    this->hide();
}

void MainWindow::on_button_exit_clicked(){
    qApp->exit();
}

void MainWindow::on_button_options_clicked()
{
    //this->hide();

    options->show();
}
