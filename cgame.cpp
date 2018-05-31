
#include "cgame.h"
#include "game.h"
Cgame::Cgame()
{
    FPS = 5;
    p1Win = false;
    p2Win = false;

}

class BufferToggle
{
    private:
        struct termios t;

    public:

        /*
         * Disables buffered input
         */

        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings

        }


        /*
         * Enables buffered input
         */

        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
            t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
};

void Cgame::initMaP(int mp, int val){
    curPos[0] = (int) BOYUT/2;
    curPos[1] = 0;
    for(int i = 0 ; i < BOYUT; ++i){
        for(int j = 0 ; j < BOYUT; ++j){
            if(mp == 1){
                map[i][j] = val;
            }else{
                enmyMap[i][j] = val;
            }
        }
    }
    map[curPos[0]][curPos[1]] = 1;
}

void Cgame::loadMap(){
    ifstream myfile;
    if(player == 1){
        myfile.open ("p1.txt");
    }else{
        myfile.open ("p2.txt");
    }
    char tmp;
    for(int i = 0; i < BOYUT; ++i){
        for(int j = 0; j < BOYUT; ++j){
            myfile >> tmp;
            if(tmp == '0'){
                map[i][j] = 0;
            }else{
                myfile >> tmp;
                map[i][j] = -1;
            }
        }
    }
    myfile.close();
}

string Cgame::drawRect(bool gameMod){
    for(int i = 0 ; i < BOYUT; ++i){
        cout<<( "-----");
    }
    cout<<("\n");
    for(int i = 0 ; i < BOYUT; ++i){
        for(int j = 0 ; j < BOYUT; ++j){
            if(gameMod){
                if(map[i][j] == -1){
                    cout<<("| 0 |"+ map[i][j]);
                }else{
                    cout<<("| %d |"+ map[i][j]);
                }
            }else{
                if(enmyMap[i][j] == -1){
                    cout<<("| %d |"+ enmyMap[i][j]);
                }else{
                    cout<<("|  %d |"+ enmyMap[i][j]);
                }
            }
        }
        cout<<("\n");
    }
    for(int i = 0 ; i < BOYUT; ++i){
        if(gameMod){
            cout<<( "-----");
        }else{
            cout<<( "------");
        }
    }
    cout<<("\n");
}

void Cgame::moveIt(int i , int j, int val, bool& stat){
    if(i < BOYUT && i >= 0){
        if(val == 0 && j == BOYUT){
            stat = false;
            enmyMap[i][j] = 0;
        }
        if(val == 1 && j == BOYUT-1){
            stat = false;
        }
        if(j < BOYUT && j >= 0){
            if(val == 0){
                enmyMap[curPos[0]][curPos[1]] = 0;
                curPos[0] = i;
                curPos[1] = j;
                enmyMap[curPos[0]][curPos[1]] = 1;
                return;
            }
            if( map[i][j] == -1 && val == 1){
                map[curPos[0]][curPos[1]] = 0;
                curPos[0] = (int) BOYUT/2;
                curPos[1] = 0;
                map[curPos[0]][curPos[1]] = 1;
                return;
            }
            map[curPos[0]][curPos[1]] = 0;
            curPos[0] = i;
            curPos[1] = j;
            map[curPos[0]][curPos[1]] = 1;
        }
    }
}

void Cgame::pReady(){
    ifstream myfileRD;
    ofstream myfileWR;
    myfileRD.open ("pInfo.txt");
    char tmpPlayer;
    char tmpP1;
    char tmpP2;
    myfileRD.get(tmpPlayer);
    myfileRD.get(tmpP1);
    myfileRD.get(tmpP2);
    myfileRD.close();
    myfileWR.open("pInfo.txt");
    if(player == 1){
        tmpP1 = '1';
    }else{
        tmpP2 = '1';
    }
    myfileWR << tmpPlayer << tmpP1 << tmpP2;
    myfileWR.close();
}

void Cgame::readyMap(){
    initMaP(2,-1);
    bool stat = true;
    int input ;

    while(stat){
        //input = getchar();
        if(minput == 'w'){
            moveIt(curPos[0]-1,curPos[1],0,stat);
        }else if(minput == 's'){
            moveIt(curPos[0]+1,curPos[1],0,stat);
        }else if(minput == 'a'){
            moveIt(curPos[0],curPos[1]-1,0,stat);
        }else if(minput == 'd'){
            moveIt(curPos[0],curPos[1]+1,0,stat);
        }
        std::system("clear");
        //drawRect(false);
        usleep((int)1000000/FPS);
    }
    ofstream myfile;
    if(player == 1){
        myfile.open ("p2.txt");
    }else{
        myfile.open ("p1.txt");
    }
    for(int i = 0; i < BOYUT; ++i){
        for(int j = 0; j < BOYUT; ++j){
            myfile << enmyMap[i][j];
        }
    }
    pReady();
    myfile.close();
}

void Cgame::readyGame(){
    bool stat = true;
    int input ;

    ofstream myfileWr;
    ifstream myfileRd;
    char tmp;

    while(stat && !p1Win && !p2Win){
        input = getchar();
        if(input == 'w'){
            moveIt(curPos[0]-1,curPos[1],1,stat);
        }else if(input == 's'){
            moveIt(curPos[0]+1,curPos[1],1,stat);
        }else if(input == 'a'){
            moveIt(curPos[0],curPos[1]-1,1,stat);
        }else if(input == 'd'){
            moveIt(curPos[0],curPos[1]+1,1,stat);
        }
        std::system("clear");
        drawRect(true);
        usleep((int)1000000/FPS);

        myfileRd.open("gInfo.txt");
        myfileRd >> tmp;
        p1Win = (tmp == '0') ? false : true;
        myfileRd >> tmp;
        p2Win = (tmp == '0') ? false : true;
        myfileRd.close();
    }
    myfileWr.open("gInfo.txt");
    if(player == 1 ){
        myfileWr << '1' << '0';
    }else if(player == 2 ){
        myfileWr << '0' << '1';
    }
    myfileWr.close();
}

void Cgame::connectPlayer(){
    ifstream myfile;
    myfile.open ("pInfo.txt");
    char t ;
    myfile.get(t);
    player = (t == '1') ? 1 : 2;
    myfile.close();
    ofstream myfile2;
    myfile2.open ("pInfo.txt");
    if(player == 1){
        myfile2 << "200";
    }else{
        myfile2 << "100";
    }
    myfile2.close();
}

/*
void GameWait(){
    ifstream myfileRd;
    ofstream myfileWr;
    char tmp;

    myfileRd.open ("pInfo.txt");
    myfileRd.get(tmp);
    myfileRd.get(p1Ready);
    myfileRd.get(p2Ready);
    myfileRd.close();
    cout << tmp <<p1Ready<<p2Ready;

    myfileWr.open("pInfo.txt");
    myfileWr.clear();
    myfileWr << tmp;
    if(player == 1){
        myfileWr << '1';
        myfileWr << p2Ready;
    }else{
        myfileWr << p1Ready;
        myfileWr << '1';
    }

}
*/

void Cgame::startGame(){
    curPos[0] = (int) BOYUT/2;
    curPos[1] = 0;
    connectPlayer();

    BufferToggle bt;
    bt.off();

    readyMap();
    ifstream myfile;

    std::system("clear");
    cout<<("oyuncu bekleniyor");

    curPos[0] = (int) BOYUT/2;
    curPos[1] = 0;

   p1Ready = '0';
   p2Ready = '0';

    while(p1Ready == '0' || p2Ready == '0' ){
        usleep(1000000);
        myfile.open ("pInfo.txt");
        myfile.get(p1Ready);
        myfile.get(p1Ready);
        myfile.get(p2Ready);
        myfile.close();
    }


    ofstream myfileWr;
    myfileWr.open("gInfo.txt");
    myfileWr.clear();
    myfileWr << "00";
    myfileWr.close();

    std::system("clear");

    loadMap();
    readyGame();

    myfileWr.open("pInfo.txt");
    myfileWr.clear();
    myfileWr << "100";
    myfileWr.close();

    if((p1Win && player == 2)||(p2Win && player == 1)){
        myfileWr.open("gInfo.txt");
        myfileWr.clear();
        myfileWr << "00";
        cout<<("LOSER...\n");
        //myfileWr.close();
    }else{
        cout<<("WİNNER!!!\n");
    }

}
void Cgame::move(char input){
    minput = input;
}


