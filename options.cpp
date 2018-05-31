#include "options.h"
#include "ui_options.h"
#include "mainwindow.h"
#include <QPixmap>


Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);

}
Options::Options(GameDes *gamedes): ui(new Ui::Options){
    ui->setupUi(this);

    this->setFixedSize(400,300);
    /*QPixmap pix = QPixmap(":/background/op2.jpg");
    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);
*/
    this->gamedes = gamedes;
    colorOfFirst = 1;
    colorOfSecond = 2;
    gamedes->get_players()[0]->setColor(colorOfFirst);
    gamedes->get_players()[1]->setColor(colorOfSecond);

}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_clicked()
{
    this->hide();
}

void Options::on_p1_blue_clicked()
{
    colorOfFirst = 1;
    gamedes->get_players()[0]->setColor(colorOfFirst);
}

void Options::on_p1_red_clicked()
{
    colorOfFirst = 2;
    gamedes->get_players()[0]->setColor(colorOfFirst);
}

void Options::on_p1_green_clicked()
{
    colorOfFirst = 3;
    gamedes->get_players()[0]->setColor(colorOfFirst);
}

void Options::on_p1_yellow_clicked()
{
    colorOfFirst = 4;
    gamedes->get_players()[0]->setColor(colorOfFirst);
}

void Options::on_p2_blue_clicked()
{
    colorOfSecond = 1;
    gamedes->get_players()[1]->setColor(colorOfSecond);
}

void Options::on_p2_red_clicked()
{
    colorOfSecond = 2;
    gamedes->get_players()[1]->setColor(colorOfSecond);
}

void Options::on_p2_green_clicked()
{
    colorOfSecond = 3;
    gamedes->get_players()[1]->setColor(colorOfSecond);
}

void Options::on_p2_yellow_clicked()
{
    colorOfSecond = 4;
    gamedes->get_players()[1]->setColor(colorOfSecond);
}


