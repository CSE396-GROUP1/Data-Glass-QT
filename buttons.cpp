#include "buttons.h"


Buttons::Buttons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buttons)
{
    ui->setupUi(this);
}

void Buttons::gdSetter(GameDes* obj){
    gd = obj;
}

void Buttons::on_p1_w_clicked()
{

    gd->p1_get()->goUp();

}

void Buttons::on_p2_w_clicked()
{
    gd->p2_get()->goUp();

}

void Buttons::on_p1_a_clicked()
{
    gd->p1_get()->goLeft();

}

void Buttons::on_p2_a_clicked()
{

    gd->p2_get()->goLeft();

}

void Buttons::on_p1_d_clicked()
{
    gd->p1_get()->goRight();
}

void Buttons::on_p2_d_clicked()
{
    gd->p2_get()->goRight();

}

void Buttons::on_p1_s_clicked()
{
    gd->p1_get()->goDown();

}

void Buttons::on_p2_s_clicked()
{
    gd->p2_get()->goDown();

}

Buttons::~Buttons()
{
    delete ui;
    delete gd;
}
