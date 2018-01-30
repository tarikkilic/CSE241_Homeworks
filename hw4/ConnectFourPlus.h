#ifndef CONNECTFOUR_PLUS
#define CONNECTFOUR_PLUS
#include "ConnectFourAbstract.h"

namespace cfGame
{
  //sadece yatay ve dikey biter
  class ConnectFourPlus : public ConnectFourAbstract
  {
  public:
      //constructor
      ConnectFourPlus();
      ConnectFourPlus(int newColumn,int newRow);
      ConnectFourPlus(int newColumn,int newRow,char newGameType);

  protected:
    //bitis fonksiyonlar,
      int isFinishedO();
      int isFinishedX();
      void gameFinishPvP();
      void gameFinishPvC();
  };

}

#endif // CONNECTFOUR_PLUS
