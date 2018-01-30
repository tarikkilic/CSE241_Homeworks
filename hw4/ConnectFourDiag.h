#ifndef CONNECTFOUR_DIAG_H
#define CONNECTFOUR_DIAG_H
#include "ConnectFourAbstract.h"

namespace cfGame
{
  class ConnectFourDiag : public ConnectFourAbstract
  {
  public:
      //constructor
      ConnectFourDiag();
      ConnectFourDiag(int newColumn,int newRow);
      ConnectFourDiag(int newColumn,int newRow,char newGameType);
  protected:
      void gameFinishPvP();
      void gameFinishPvC();
      int crossFinishedO();
      int crossFinishedX();
  };
}


#endif // CONNECTFOUR_DIAG_H
