#ifndef CGAME_H
#define CGAME_H
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>


using namespace std;

class Cgame
{
public:
    Cgame();
    void startGame();
    void move(char input);
    string drawRect(bool gameMod);
    int map [BOYUT][BOYUT];
    int enmyMap [BOYUT][BOYUT];

protected:

    static const int BOYUT = 10 ;
    //int map [BOYUT][BOYUT];
    int curPos[2];
    int FPS ;

    int player;
    bool p1Win ;
    bool p2Win ;

    char p1Ready ;
    char p2Ready ;

    //int enmyMap [BOYUT][BOYUT];
    char minput;

    private:
    int mainGame(void);
    void initMaP(int mp, int val);
    void loadMap();
    void moveIt(int i , int j, int val, bool& stat);
    void pReady();
    void readyMap();
    void readyGame();
    void connectPlayer();
};

#endif // CGAME_H
