#include <iostream>
#include <cstdlib>//exit
#include "ConnectFourDiag.h"
#include "ConnectFourUndo.h" //Plus undonun icinde
using namespace std;
using namespace cfGame; //ConnectFour namespace
int main()
{
    char gameMode;
    cout << "Oyun modu secin: ";
    cin >> gameMode;
    //Çapraz bitirme
    if(gameMode == 'D')
    {
        ConnectFourDiag obje;
        obje.playGame();
    }
    //Yatay dikey bitirme
    else if(gameMode == 'P')
    {
        ConnectFourPlus obje;
        obje.playGame();
    }
    //Geri almali oyun
    else if(gameMode == 'U')
    {
        ConnectFourUndo obje;
        obje.playGame();
    }
    else if(cin.fail()){
      exit(1);
    }

    return 0;
}
