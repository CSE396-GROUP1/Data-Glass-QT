#include "someonewon.h"
#include "ui_someonewon.h"


SomeoneWon::SomeoneWon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SomeoneWon)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    p1_score = 0;
    p2_score = 0;
}

void SomeoneWon::p1_won(){
    p1_score++;
    displayScore();
}


void SomeoneWon::p2_won(){
    p2_score++;
    displayScore();
}

void SomeoneWon::displayScore(){

    ui->lcdNumber->display(p1_score);
    ui->lcdNumber_2->display(p2_score);
}

SomeoneWon::~SomeoneWon()
{
    delete ui;
}
