#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>
#include "ui_buttons.h"
#include "gamedes.h"

namespace Ui {
class Buttons;
}

class Buttons : public QWidget
{
    Q_OBJECT

public:
    explicit Buttons(QWidget *parent = 0);
    void gdSetter(GameDes*);
    ~Buttons();

private slots:
    void on_p1_w_clicked();
    void on_p2_w_clicked();
    void on_p1_a_clicked();
    void on_p2_a_clicked();
    void on_p1_d_clicked();
    void on_p2_d_clicked();
    void on_p1_s_clicked();
    void on_p2_s_clicked();

private:
    Ui::Buttons *ui;
    GameDes* gd;
};

#endif // BUTTONS_H
