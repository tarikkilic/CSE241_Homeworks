#ifndef CONNECTFOUR_ABSTRACT_H
#define CONNECTFOUR_ABSTRACT_H
#include "Cell.h"
#include <string>
using namespace std;

namespace cfGame
{
  class ConnectFourAbstract
  {
  public:
      //construct
      ConnectFourAbstract();
      ConnectFourAbstract(int newColumn,int newRow);
      ConnectFourAbstract(int newColumn,int newRow,char newGameType);
      virtual ~ConnectFourAbstract();//Destructor
      ConnectFourAbstract(const ConnectFourAbstract& obje);
      ConnectFourAbstract& operator=(const ConnectFourAbstract& obje);
      bool getDone()const{return done;}
      //Oyun dongusuiceren fonksiyon
      virtual void playGame();
      //Load ve Save yapan Fonksiyonlar
      virtual void loadGame(string filename);
      virtual void saveGame(string filename)const;
      //board icin yer alir
      void initCells();

      //satir sutunu kullanicadan ister.
      void inputRow();
      void inputColumn();

      //gameCells i ekrana bastirir
      void printCells();
      //oyun tipini kullanicidan alir
      void inputGameType();

  protected:
      //private fonksiyonlar
      //parametreli olan user inputu alir,parametresiz computer hamlesi.
      virtual void play(string newPosition);
      virtual void play();
      //atacagi yeri kullanicidan ister
      void inputPos(string& pos);
      //Oyun modlarini ayristirdim.
      virtual void PVP();
      virtual void PVC();

      int isFilled()const;
      void toLower(int x,int y);
      int isLegal(int newX,int newY)const;
      //bilgisayarin hamlenin nasil yapilcagina karar verir.
      int computerAI();
      //Bilgisayar en uygun atilacak yeri kontrol eder
      int computer3Right();
      int computer3Left();
      int computer3Up();
      int computer2Left();
      int computer2Right();
      int computer2Up();
      int computerUp();
      int computerRight();
      int computerLeft();
      int computer3RightO();
      int computer3LeftO();
      int computer3UpO();
      int computer2LeftO();
      int computer2RightO();
      int computer2UpO();
      int computerUpO();
      int computerRightO();
      int computerLeftO();
      //arada bosluk varsa ve tehlikeliyse oraya atar.
      int computerMid();
      //Oyun bitis fonksiyonlari
      virtual void gameFinishPvP() = 0;
      virtual void gameFinishPvC() = 0;

      Cell** gameCells;
      int row;
      int column;
      //hamle sirasini tutan degiskenler
      bool player1;
      bool player2;
      bool computer;
      //oyunun bitip bitmedigini tutan degisken
      bool done;
      char gameType;
      bool flag;
  };
}




#endif
