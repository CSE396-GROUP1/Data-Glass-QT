#ifndef SOMEONEWON_H
#define SOMEONEWON_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QLCDNumber>

namespace Ui {
class SomeoneWon;
}

class SomeoneWon : public QWidget
{
    Q_OBJECT

public:
    explicit SomeoneWon(QWidget *parent = 0);
    void displayScore();
    void p1_won();
    void p2_won();

    ~SomeoneWon();

private:
    Ui::SomeoneWon *ui;
    int p1_score;
    int p2_score;
};

#endif // SOMEONEWON_H
