#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <iostream>
#include "gamedes.h"
#include <QTextEdit>

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    int colorOfFirst;
    int colorOfSecond;
    std::string nameOfFirst;
    std::string nameOfSecond;
    explicit Options(QWidget *parent = 0);
    Options(GameDes* gamedes);
    ~Options();

private slots:
    void on_pushButton_clicked();

    void on_p1_blue_clicked();

    void on_p1_red_clicked();

    void on_p1_green_clicked();

    void on_p1_yellow_clicked();

    void on_p2_blue_clicked();

    void on_p2_red_clicked();

    void on_p2_green_clicked();

    void on_p2_yellow_clicked();

private:
    Ui::Options *ui;
    GameDes* gamedes;
};

#endif // OPTIONS_H
